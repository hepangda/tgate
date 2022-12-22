# Copyright (c) hepangda
#
# This source code is licensed under the Apache license found in the
# LICENSE file in the root directory of this source tree.

include_directories(..)

add_executable(tg_test_fastcgi
        fastcgi_test.cc
        )

target_link_libraries(tg_test_fastcgi tg_fastcgi)
