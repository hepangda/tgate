# Copyright (c) hepangda
#
# This source code is licensed under the Apache license found in the
# LICENSE file in the root directory of this source tree.

include_directories(..)

add_executable(tg_test_http
        http_base_test.cc
)

add_executable(tg_test_http_request
        http_request_test.cc
)

target_link_libraries(tg_test_http tg_http)
target_link_libraries(tg_test_http_request tg_http)
