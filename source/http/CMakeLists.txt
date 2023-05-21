# Copyright (c) hepangda
#
# This source code is licensed under the Apache license found in the
# LICENSE file in the root directory of this source tree.

include_directories(..)

add_library(tg_http
        http_base.cc
        http_base.h
        http_constants.h
        http_request.cc
        http_request.h
        http_response.cc
        http_response.h
        )
