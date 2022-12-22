/**
 * Copyright (c) hepangda
 *
 * This source code is licensed under the Apache license found in the
 * LICENSE file in the root directory of this source tree.
 */
#pragma once

#include "asio.hpp"
#include "source/foundation/foundation.h"

namespace tg {

class ConnectionManager {
 public:
  static asio::awaitable<void> echo(asio::ip::tcp::socket socket) {
    try {
      char data[1024];
      for (;;) {
        std::size_t n = co_await socket.async_read_some(asio::buffer(data), asio::use_awaitable);
        co_await async_write(socket, asio::buffer(data, n), asio::use_awaitable);
      }
    } catch (std::exception &e) {
      std::printf("echo Exception: %s\n", e.what());
    }
  }

  static asio::awaitable<void> mainLoop() {
    auto executor = co_await asio::this_coro::executor;
    asio::ip::tcp::acceptor acceptor(executor, {asio::ip::tcp::v4(), 5555});
    for (;;) {
      asio::ip::tcp::socket socket = co_await acceptor.async_accept(asio::use_awaitable);
      asio::co_spawn(executor, echo(std::move(socket)), asio::detached);
    }
  }

  void construct() {
    asio::co_spawn(io_context_, mainLoop(), asio::detached);
    io_context_.run();
  }

 private:
  asio::io_context io_context_{1};
};

}  // namespace tg
