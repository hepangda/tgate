# Copyright (c) hepangda
#
# This source code is licensed under the Apache license found in the
# LICENSE file in the root directory of this source tree.

cmake_minimum_required(VERSION 3.23)
project(tgate)

set(CMAKE_CXX_STANDARD 23)

enable_testing()
find_package(GTest CONFIG REQUIRED)
link_libraries(GTest::gmock GTest::gtest)

find_package(jsoncpp CONFIG REQUIRED)
link_libraries(jsoncpp_object jsoncpp_static JsonCpp::JsonCpp)

include_directories(.)

add_subdirectory(source/core)
add_subdirectory(source/foundation)
add_subdirectory(source/fastcgi)
add_subdirectory(source/http)
add_subdirectory(test/core)
add_subdirectory(test/fastcgi)
add_subdirectory(test/http)

add_executable(tgate source/main.cc)

target_link_libraries(tgate tg_core tg_foundation tg_http tg_fastcgi)
