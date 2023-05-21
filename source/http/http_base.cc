/**
 * Copyright (c) hepangda
 *
 * This source code is licensed under the Apache license found in the
 * LICENSE file in the root directory of this source tree.
 */
#include "http_base.h"

#include "source/http/http_constants.h"

namespace tg {

namespace detail {

auto findLine(const std::string &view, std::string::const_iterator first) {
  auto line_end = std::search(first, view.cend(), http_const::LINE_SEPARATOR.begin(), http_const::LINE_SEPARATOR.end());
  return std::make_pair(first, line_end);
}

auto extractHeader(std::string::const_iterator first, std::string::const_iterator last) {
  auto line_end = std::find(first, last, '\r');
  auto colon = std::find(first, line_end, ':');
  if (colon == line_end) {
    throw std::runtime_error("Invalid header");
  }
  return std::make_pair(std::string_view{first, colon}, std::string_view{colon + 1, line_end});
}

std::string_view trim(std::string_view s) {
  auto is_space = [](char c) { return std::isspace(static_cast<unsigned char>(c)); };

  auto begin = std::ranges::find_if_not(s, is_space);
  auto end = std::ranges::find_if_not(s.rbegin(), s.rend(), is_space).base();

  return std::string_view(&*begin, std::distance(begin, end));
}

}  // namespace detail

void HttpBase::construct(std::unique_ptr<std::string> origin) {
  if (!origin) {
    throw std::invalid_argument("Origin string is null.");
  }

  origin_ = std::move(origin);

  bool is_firstline = true;
  bool last_emptyline = false;
  for (const auto word : std::views::split(*origin_, http_const::LINE_SEPARATOR)) {
    if (is_firstline) {
      parseFirstLine(word);
      first_line_ = std::string_view{word};
      is_firstline = false;
    } else {
      if (word.size() == 0) {
        last_emptyline = true;
      } else if (last_emptyline) {
        entity_ = std::string_view{word.begin(), origin_->end()};
        break;
      } else {
        parseHeaders(word);
      }
    }
  }
}

void HttpBase::parseHeaders(std::ranges::subrange<std::string::iterator, std::string::iterator> subrange) {
  auto delimiter = std::ranges::find(subrange, ':');

  if (delimiter == subrange.end()) {
    return;
    throw std::runtime_error("Delimiter not found");
  }

  std::string_view key(&*subrange.begin(), std::distance(subrange.begin(), delimiter));
  std::string_view value(&*std::next(delimiter), std::distance(std::next(delimiter), subrange.end()));

  headers_.emplace(detail::trim(key), detail::trim(value));

  return;
}

std::optional<std::string_view> HttpBase::header(const std::string_view &key) const {
  if (headers_.contains(key)) {
    return headers_.at(key);
  }

  return std::nullopt;
}

void HttpBase::add_header(const std::string &key, const std::string &val) {
  // auto start_iter = header_end_;
  // origin_->insert(header_end_, key.begin(), key.end());
  // std::advance(header_end_, key.length());
  // std::string_view key_sv{&*start_iter, key.length()};

  // origin_->insert(header_end_, http_const::HEADER_SEPARATOR.begin(), http_const::HEADER_SEPARATOR.end());
  // std::advance(header_end_, http_const::HEADER_SEPARATOR.length());

  // start_iter = header_end_;
  // origin_->insert(header_end_, val.begin(), val.end());
  // std::advance(header_end_, val.length());
  // std::string_view val_sv{&*start_iter, val.length()};

  // origin_->insert(header_end_, http_const::LINE_SEPARATOR.begin(), http_const::LINE_SEPARATOR.end());
  // std::advance(header_end_, http_const::LINE_SEPARATOR.length());

  // headers_.emplace(key_sv, val_sv);
}

void HttpBase::clear_header() {
  // headers_.clear();
  // origin_->erase(header_begin_, header_end_);
  // header_end_ = header_begin_;
}

}  // namespace tg