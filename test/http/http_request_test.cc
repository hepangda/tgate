/**
 * Copyright (c) hepangda
 *
 * This source code is licensed under the Apache license found in the
 * LICENSE file in the root directory of this source tree.
 */
#include "source/http/http_request.h"

#include "gtest/gtest.h"

using namespace tg;

TEST(HttpRequestTest, ValidRequest) {
  auto request_str = std::make_unique<std::string>(
      "GET /test HTTP/1.1\r\n"
      "Host: www.example.com\r\n"
      "Connection: keep-alive\r\n"
      "User-Agent: Mozilla/5.0 (X11; Linux x86_64)\r\n"
      "\r\n");

  HttpRequest request;
  request.construct(std::move(request_str));

  ASSERT_EQ(request.path(), "/test");
  ASSERT_EQ(request.http_version(), "HTTP/1.1");
  ASSERT_EQ(request.http_major(), 1);
  ASSERT_EQ(request.http_minor(), 1);

  auto headers = request.headers();
  ASSERT_EQ(headers.size(), 3);
  ASSERT_EQ(headers["Host"], " www.example.com");
  ASSERT_EQ(headers["Connection"], " keep-alive");
  ASSERT_EQ(headers["User-Agent"], " Mozilla/5.0 (X11; Linux x86_64)");
}

TEST(HttpRequestTest, InvalidRequest) {
  std::unique_ptr<std::string> request_str = std::make_unique<std::string>(
      "GET /test\r\n"
      "Host: www.example.com\r\n"
      "Connection: keep-alive\r\n"
      "User-Agent: Mozilla/5.0 (X11; Linux x86_64)\r\n"
      "\r\n");

  HttpRequest request;
  ASSERT_THROW(request.construct(std::move(request_str)), std::runtime_error);
}

TEST(HttpRequestTest, NullRequest) {
  std::unique_ptr<std::string> request_str = nullptr;

  HttpRequest request;
  ASSERT_THROW(request.construct(std::move(request_str)), std::invalid_argument);
}

TEST(HttpRequestTest, EmptyRequest) {
  std::unique_ptr<std::string> request_str = std::make_unique<std::string>("");

  HttpRequest request;
  ASSERT_THROW(request.construct(std::move(request_str)), std::runtime_error);
}

TEST(HttpRequestTest, EntityRequest) {
  std::unique_ptr<std::string> request_str = std::make_unique<std::string>(
      "POST /test HTTP/1.1\r\n"
      "Host: www.example.com\r\n"
      "Content-Type: application/x-www-form-urlencoded\r\n"
      "Content-Length: 13\r\n"
      "\r\n"
      "field1=value1");

  HttpRequest request;
  ASSERT_NO_THROW(request.construct(std::move(request_str)));

  ASSERT_EQ(request.path(), "/test");
  ASSERT_EQ(request.http_version(), "HTTP/1.1");
  ASSERT_EQ(request.http_major(), 1);
  ASSERT_EQ(request.http_minor(), 1);

  auto headers = request.headers();
  ASSERT_EQ(headers.size(), 3);
  ASSERT_EQ(headers["Host"], " www.example.com");
  ASSERT_EQ(headers["Content-Type"], " application/x-www-form-urlencoded");
  ASSERT_EQ(headers["Content-Length"], " 13");

  ASSERT_TRUE(request.have_entity());
  // ASSERT_EQ(std::string(request.entity_begin(), request.entity_end()), "field1=value1");
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}