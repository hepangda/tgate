/**
 * Copyright (c) hepangda
 *
 * This source code is licensed under the Apache license found in the
 * LICENSE file in the root directory of this source tree.
 */
#pragma once

#include <algorithm>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <memory>
#include <optional>
#include <ranges>
#include <string>
#include <string_view>
#include <unordered_map>

#include "source/foundation/foundation.h"
#include "source/http/http_constants.h"

namespace tg {

class HttpBase : public Noncopyable {
 public:
  std::string_view origin() { return *origin_; }
  void print_headers() {
    for (auto [k, v] : headers_) {
      std::cout << k << http_const::HEADER_SEPARATOR << v << std::endl;
    }
  }

  void construct(std::unique_ptr<std::string> origin);

  // Accessors
  void http_version(std::string_view http_version) { http_version_ = http_version; }
  std::string_view http_version() const { return http_version_; }

  void first_line(std::string_view first_line) { first_line_ = first_line; }
  std::string_view first_line() const { return first_line_; }


  const std::unordered_map<std::string_view, std::string_view> &headers() const { return headers_; }

  std::optional<std::string_view> header(const std::string_view &key) const;
  void add_header(const std::string &key, const std::string &val);
  void clear_header();

  bool have_entity() const { return entity_ && entity_->size() > 0; }
  std::optional<std::string_view> entity() const { return entity_; }

 protected:
  std::unique_ptr<std::string> origin_;

  std::string_view http_version_;
  std::string_view first_line_;
  std::optional<std::string_view> header_lines_;
  std::optional<std::string_view> entity_;

  std::unordered_map<std::string_view, std::string_view> headers_;

 protected:
  virtual void parseFirstLine(std::ranges::subrange<std::string::iterator, std::string::iterator>) = 0;
  void parseHeaders(std::ranges::subrange<std::string::iterator, std::string::iterator> a);
  void parseEntity();
};

}  // namespace tg
