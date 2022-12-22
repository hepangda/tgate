/**
 * Copyright (c) hepangda
 *
 * This source cod is licensed under the Apache license found in the
 * LICENSE file in the root directory of this source tree.
 */
#include "http_base.h"

#include <cstring>

#include "source/http/http_constants.h"

namespace tg {

std::optional<std::string_view> HttpBase::header(const std::string_view &key) const {
  if (headers_.contains(key)) {
    return headers_.at(key);
  }

  return std::nullopt;
}

void HttpBase::add_header(const std::string &key, const std::string &val) {
  auto start_iter = header_end_;
  origin_->insert(header_end_, key.begin(), key.end());
  std::advance(header_end_, key.length());
  std::string_view key_sv{&*start_iter, key.length()};

  origin_->insert(header_end_, http_const::HEADER_SEPARATOR.begin(), http_const::HEADER_SEPARATOR.end());
  std::advance(header_end_, http_const::HEADER_SEPARATOR.length());

  start_iter = header_end_;
  origin_->insert(header_end_, val.begin(), val.end());
  std::advance(header_end_, val.length());
  std::string_view val_sv{&*start_iter, val.length()};

  origin_->insert(header_end_, http_const::LINE_SEPARATOR.begin(), http_const::LINE_SEPARATOR.end());
  std::advance(header_end_, http_const::LINE_SEPARATOR.length());

  headers_.emplace(key_sv, val_sv);
}

void HttpBase::clear_header() {
  headers_.clear();
  origin_->erase(header_begin_, header_end_);
  header_end_ = header_begin_;
}

void HttpBase::construct(const std::string &test) {
  origin_ = std::make_unique<std::string>(test);
  header_begin_ = header_end_ = origin_->cbegin();

  auto offset = origin_->find(http_const::LINE_SEPARATOR);
  if (offset != std::string::npos) {
    std::advance(header_begin_, offset);

    offset = origin_->find(http_const::HEADER_END_IDENTIFIER, offset);
    std::advance(header_end_, offset);
  } else {
    throw std::runtime_error("");
  }
}

bool HttpBase::have_entity() const { return have_entity_; }

}  // namespace tg