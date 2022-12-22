/**
* Copyright (c) hepangda
*
* This source cod is licensed under the Apache license found in the
* LICENSE file in the root directory of this source tree.
*/
#pragma once

namespace tg {

class Noncopyable {
 public:
  // delete copy constructor and copy assign operator to avoid copy
  Noncopyable(const Noncopyable &) = delete;
  Noncopyable &operator=(const Noncopyable &) = delete;

 protected:
  // declared `protected` to avoid get instance of `Noncopyable` itself
  constexpr Noncopyable() = default;
  ~Noncopyable() = default;
};

}// namespace tg
