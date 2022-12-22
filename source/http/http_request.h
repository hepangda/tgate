/**
 * Copyright (c) hepangda
 *
 * This source cod is licensed under the Apache license found in the
 * LICENSE file in the root directory of this source tree.
 */
#pragma once

#include "http_base.h"

namespace tg {

class HttpRequest : public HttpBase {
 private:
  int http_major_;
  int http_minor_;
  std::string http_version_;
};

}  // namespace tg
