/**
 * Copyright (c) hepangda
 *
 * This source code is licensed under the Apache license found in the
 * LICENSE file in the root directory of this source tree.
 */
#pragma once

#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

#include "source/foundation/foundation.h"
#include "source/http/http_constants.h"

namespace tg {

class HttpBase : public Noncopyable {
 public:
  std::optional<std::string_view> header(const std::string_view &key) const;
  void add_header(const std::string &key, const std::string &val);
  void clear_header();

  std::string_view origin() { return *origin_; }
  void print_headers() {
    for (auto [k, v] : headers_) {
      std::cout << k << http_const::HEADER_SEPARATOR << v << std::endl;
    }
  }

  void construct(const std::string &test);

  bool have_entity() const;

 private:
  std::string_view first_line_;
  std::string_view http_version_;
  std::unordered_map<std::string_view, std::string_view> headers_;
  std::unique_ptr<std::string> origin_;
  std::string::const_iterator first_line_begin_;
  std::string::const_iterator first_line_end_;
  std::string::const_iterator header_begin_;
  std::string::const_iterator header_end_;
  bool have_entity_;
  std::string::const_iterator entity_begin_;
  std::string::const_iterator entity_end_;
};

}  // namespace tg
