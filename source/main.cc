/**
 * Copyright (c) hepangda
 *
 * This source cod is licensed under the Apache license found in the
 * LICENSE file in the root directory of this source tree.
 */
#include <iostream>

#include "source/core/connection_manager.h"

int main() {
  tg::ConnectionManager connection_manager;
  connection_manager.construct();
  std::cout << "Hello, World!" << std::endl;
  return 0;
}
