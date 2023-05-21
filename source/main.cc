/**
 * Copyright (c) hepangda
 *
 * This source code is licensed under the Apache license found in the
 * LICENSE file in the root directory of this source tree.
 */
#include <iostream>

#include "source/core/connection_manager.h"
#include "source/http/http_request.h"

using namespace tg;

#define ASSERT_EQ(A, B) std::cout << "[" << A << "," << B << "]\n";



int main() {
  std::unique_ptr<std::string> request_str = std::make_unique<std::string>(
      "POST /test HTTP/1.1\r\n"
      "Host: www.example.com\r\n"
      "Content-Type: application/x-www-form-urlencoded\r\n"
      "Content-Length: 13\r\n"
      "\r\n"
      "field1=value1");

  HttpRequest request;
  request.construct(std::move(request_str));

  // ASSERT_EQ(request.path(), "/test");
  // ASSERT_EQ(request.http_version(), "HTTP/1.1");
  // ASSERT_EQ(request.http_major(), 1);
  // ASSERT_EQ(request.http_minor(), 1);

  auto headers = request.headers();
  request.print_headers();
  ASSERT_EQ(headers.size(), 3);
  ASSERT_EQ(headers["Host"], "www.example.com");
  ASSERT_EQ(headers["Content-Type"], "keep-alive");
  ASSERT_EQ(headers["Content-Length"], "Mozilla/5.0 (X11; Linux x86_64)");
  ASSERT_EQ(request.entity(),"");

  // tg::ConnectionManager connection_manager;
  // connection_manager.construct();
  // std::cout << "Hello, World!" << std::endl;
  return 0;
}
