/**
 * Copyright (c) hepangda
 *
 * This source cod is licensed under the Apache license found in the
 * LICENSE file in the root directory of this source tree.
 */
#pragma once

#include <string_view>

namespace tg::http_const {

namespace details {

template <int BIT>
constexpr uint64_t set_low() {
  static_assert(BIT < 32, "bit must small than 32");
  return 1ULL << BIT;
}

template <int BIT>
constexpr uint64_t set_high() {
  static_assert(BIT < 32, "bit must small than 32");
  return 1ULL << (BIT + 32);
}

}  // namespace details

using namespace std::string_view_literals;

constexpr auto LINE_SEPARATOR = "\r\n"sv;
constexpr auto HEADER_SEPARATOR = ": "sv;
constexpr auto HEADER_END_IDENTIFIER = "\r\n\r\n"sv;
constexpr auto STATUS_OK = "OK"sv;
constexpr auto STATUS_PARTIAL_CONTENT = "Partial Content";

enum class HttpStatusCode : int {
  NOT_DONE = -1,
  OK = 200,
  PARTIAL_CONTENT = 206,
  MOVED_PERMANENTLY = 301,
  FOUND = 302,
  BAD_REQUEST = 400,
  FORBIDDEN = 403,
  METHOD_NOT_ALLOWED = 405,
  LENGTH_REQUIRED = 411,
  REQUEST_ENTITY_TOO_LARGE = 413,
  INTERNAL_SERVER_ERROR = 500,
  NOT_IMPLEMENTED = 501,
  BAD_GATEWAY = 502,
  GATEWAY_TIMEOUT = 504,
  HTTP_VERSION_NOT_SUPPORTED = 505,
};

enum class HttpFlags : unsigned long {
  NOTHING = 0,
  KEEP_ALIVE = 1,
};

enum class HttpParserState : uint64_t {
  BEGIN = 0,
  METHOD_OPTIONS,
  METHOD_HEAD,
  METHOD_GET,
  METHOD_POST,
  METHOD_ALMOST_DONE,
  METHOD_DONE,

  URI_START,
  URI,
  URI_END,

  VER_HTTP_AND_SLASH,
  VER_MAJOR,
  VER_DOT,
  VER_MINOR,
  VER_END,

  CR,
  CRLF,
  CRLFCR,

  HEADER_KEY,
  HEADER_COLON,
  HEADER_VALUE,
  HEADER_CRLF,

  WAITING_ENTITY,
  DONE,

  // ERROR
  NEED_MORE = details::set_high<1>(),
  PARSED = details::set_high<2>(),
  INVALID_METHOD = details::set_high<3>(),
  INVALID_URI = details::set_high<4>(),
  INVALID_VERSION = details::set_high<5>(),
  INVALID_CONTENT_LENGTH = details::set_high<6>(),
  INVALID_HEADER = details::set_high<7>(),
  UNRECOGNIZED_CHAR = details::set_high<8>(),
  UNEXCEPTED_END = details::set_high<9>(),
  ENTITY_TOO_LARGE = details::set_high<10>(),
  UNSUPPORTED_VERSION = details::set_high<11>(),
  OTHER = details::set_high<12>(),
};

}  // namespace tg::http_const
