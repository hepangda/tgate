# Copyright (c) hepangda
#
# This source cod is licensed under the Apache license found in the
# LICENSE file in the root directory of this source tree.

include_directories(..)

add_library(tg_core
        tgate.cc
        tgate.h
        connection_manager.cc
        connection_manager.h
        )
