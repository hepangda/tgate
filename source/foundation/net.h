/**
 * Copyright (c) hepangda
 *
 * This source cod is licensed under the Apache license found in the
 * LICENSE file in the root directory of this source tree.
 */
#pragma once

#include <algorithm>
#include <bit>
#include <concepts>
#include <cstdlib>

#include "asio.hpp"
#include "source/foundation/foundation.h"

namespace tg {

namespace nl = asio;

namespace net {

template <std::integral T>
constexpr T SwapByteEndian(T value) noexcept {
  static_assert(std::has_unique_object_representations_v<T>, "T may not have padding bits");
  auto value_representation = std::bit_cast<std::array<std::byte, sizeof(T)>>(value);
  std::reverse(std::begin(value_representation), std::end(value_representation));
  return std::bit_cast<T>(value_representation);
}

constexpr bool IsBigEndian() { return std::endian::native == std::endian::big; }

constexpr bool IsLittleEndian() { return std::endian::native == std::endian::little; }

template <std::integral T>
auto ToNetworkEndian(T val) noexcept {
  static_assert(IsLittleEndian() || IsBigEndian(), "Mixed endian machine is not supported");
  if constexpr (IsLittleEndian()) {
    return SwapByteEndian(val);
  }
  return val;
}

template <std::integral T>
auto ToLocalEndian(T val) noexcept {
  static_assert(IsLittleEndian() || IsBigEndian(), "Mixed endian machine is not supported");
  if constexpr (IsLittleEndian()) {
    return SwapByteEndian(val);
  }
  return val;
}

}  // namespace net

}  // namespace tg