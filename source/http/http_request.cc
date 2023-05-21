/**
 * Copyright (c) hepangda
 *
 * This source code is licensed under the Apache license found in the
 * LICENSE file in the root directory of this source tree.
 */
#include "http_request.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

namespace tg {

void HttpRequest::parseFirstLine(std::ranges::subrange<std::string::iterator, std::string::iterator>) {
  // first_line_begin_ = origin_->cbegin();
  // first_line_end_ = std::find(first_line_begin_, origin_->cend(), '\n');

  // if (first_line_end_ == origin_->cend()) {
  //   throw std::runtime_error("Failed to parse the first line: no line break found.");
  // }

  // first_line_ = std::string_view(&*first_line_begin_, std::distance(first_line_begin_, first_line_end_));

  // auto FIRSTLINE = std::string(first_line_);
  // std::istringstream iss(FIRSTLINE);
  // std::string method;
  // // iss >> method;
  // // iss >> path_ >> http_version_;

  // if (sscanf(http_version_.data(), "HTTP/%d.%d", &http_major_, &http_minor_) != 2) {
  //   throw std::runtime_error("Failed to parse HTTP version.");
  // }

  // header_begin_ = first_line_end_ + 1;
}



}  // namespace tg