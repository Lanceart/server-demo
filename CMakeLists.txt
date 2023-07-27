cmake_minimum_required(VERSION 2.8)
project(coolserver)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O3 -g -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function -lyaml-cpp")

include_directories(.)
include_directories(/home/lance/Documents/setting/yaml-cpp-master/yaml-cpp-master/include)
link_directories(/apps/coolserver/lib)

set(LIB_SRC
    coolserver/log.cc
    coolserver/util.cc
    coolserver/config.cc
    )

add_library(coolserver SHARED ${LIB_SRC})

add_executable(test tests/test.cc)
add_dependencies(test coolserver)
target_link_libraries(test coolserver)

add_executable(test_config tests/test_config.cc)
add_dependencies(test_config coolserver)
target_link_libraries(test_config coolserver yaml-cpp)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
