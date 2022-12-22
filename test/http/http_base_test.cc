/**
 * Copyright (c) hepangda
 *
 * This source code is licensed under the Apache license found in the
 * LICENSE file in the root directory of this source tree.
 */
#include "source/http/http_base.h"

#include <gtest/gtest.h>

class HttpBaseTest : public testing::Test {
 public:
  static void SetUpTestCase() {}
  static void TearDownTestCase() {}
  void SetUp() override { http_base.construct("GET / HTTP/1.1\r\na:b\r\nc:d\r\n"); }
  void TearDown() override {}

 protected:
  tg::HttpBase http_base;
};

TEST_F(HttpBaseTest, ONLY_ONE) {
  http_base.add_header("hello", "world");
  EXPECT_EQ(http_base.origin(), "hello: world\r\n");
  http_base.print_headers();
}

TEST_F(HttpBaseTest, ADD_TWO) {
  http_base.add_header("hello", "world");
  http_base.add_header("a1", "b1");
  EXPECT_EQ(http_base.origin(), "hello: world\r\na1: b1\r\n");
  http_base.print_headers();
}

TEST_F(HttpBaseTest, CONTAINS) {
  http_base.add_header("hello", "world");
  http_base.add_header("a1", "b1");
  EXPECT_EQ(http_base.header("hello"), "world");
  EXPECT_EQ(http_base.header("a1"), "b1");
  EXPECT_EQ(http_base.header("anything else"), std::nullopt);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}