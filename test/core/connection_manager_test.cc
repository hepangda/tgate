/**
 * Copyright (c) hepangda
 *
 * This source code is licensed under the Apache license found in the
 * LICENSE file in the root directory of this source tree.
 */
#include "source/core/connection_manager.h"

#include <gtest/gtest.h>

#include <thread>

class ConnectionManager : public testing::Test {
 public:
  static void SetUpTestCase() {}
  static void TearDownTestCase() {}
  void SetUp() override {}
  void TearDown() override {}

 private:
  static tg::ConnectionManager connection_manager_;
  static std::unique_ptr<std::thread> thread_;
};

TEST_F(ConnectionManager, ONLY_ONE) {}
