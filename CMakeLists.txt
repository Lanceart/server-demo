cmake_minimum_required(VERSION 2.8)
project(coolserver)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O3 -g -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function")

set(LIB_SRC
    coolserver/log.cc
    )

#add_library(coolserver SHARED ${LIB_SRC})
