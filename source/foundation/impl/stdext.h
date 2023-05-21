/**
 * Copyright (c) hepangda
 *
 * This source code is licensed under the Apache license found in the
 * LICENSE file in the root directory of this source tree.
 */
#pragma once

#include <array>
#include <concepts>
#include <cstddef>
#include <cstring>

// namespace std {

// template <class To, class From>
// using BitCast_ReturnType = std::enable_if_t<
//     sizeof(To) == sizeof(From) && std::is_trivially_copyable_v<From> && std::is_trivially_copyable_v<To>, To>;

// template <class To, class From>
// BitCast_ReturnType<To, From> bit_cast(const From &src) noexcept {
//   static_assert(std::is_trivially_constructible_v<To>,
//                 "This implementation additionally requires destination type_ to be trivially constructible");
//   To dst;
//   std::memcpy(&dst, &src, sizeof(To));
//   return dst;
// }

// }  // namespace std