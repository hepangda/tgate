/**
 * Copyright (c) hepangda
 *
 * This source code is licensed under the Apache license found in the
 * LICENSE file in the root directory of this source tree.
 */
#pragma once

#include "http_base.h"

namespace tg {

class HttpRequest : public HttpBase {
 public:
  // accessors
  void http_major(int http_major) { http_major_ = http_major; }
  int http_major() const { return http_major_; }

  void http_minor(int http_minor) { http_minor_ = http_minor; }
  int http_minor() const { return http_minor_; }

  void path(std::string_view path) { path_ = path; }
  std::string_view path() const { return path_; }

  // Parse function
  void parseFirstLine(std::ranges::subrange<std::string::iterator, std::string::iterator>);
 private:
  int http_major_;
  int http_minor_;
  std::string_view http_version_;
  std::string_view path_;
};

}  // namespace tg
