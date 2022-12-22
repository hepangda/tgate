# Copyright (c) hepangda
#
# This source cod is licensed under the Apache license found in the
# LICENSE file in the root directory of this source tree.

find_package(asio CONFIG REQUIRED)

include_directories(..)

add_library(tg_foundation
        impl/copyable.h
        impl/noncopyable.h
        impl/interface.h
        foundation.h
        net.h
        impl/stdext.h
        )

target_link_libraries(tg_foundation PUBLIC
        asio asio::asio)
