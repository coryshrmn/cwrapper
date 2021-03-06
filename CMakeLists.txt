# Copyright 2017 Cory Sherman
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# The cwrapper library is header only, and does not require any compilation.
# This CMakeLists.txt builds cwrapper tests.

cmake_minimum_required(VERSION 3.2.2 FATAL_ERROR)

project(cwrapper C CXX)

enable_testing()

include_directories(include)

set(CWRAPPER_HEADERS
    "include/cwrapper/enum.hpp"
    "include/cwrapper.hpp"
    "include/cwrapper/resource.hpp"
)

set(CWRAPPER_TEST_SOURCE
    "test/enum.cpp"
    "test/resource.cpp"
)

# main test
add_executable(cwrapper-test
    ${CWRAPPER_HEADERS}
    ${CWRAPPER_TEST_SOURCE}
)
add_test(NAME cwrapper-test COMMAND cwrapper-test)

set_property(TARGET ${PROJECT_NAME}-test PROPERTY CXX_STANDARD 14)
set_property(TARGET ${PROJECT_NAME}-test PROPERTY CXX_STANDARD_REQUIRED ON)

# Download and compile Googletest library
include(ExternalProject)
set(gtest_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/gtest-install")
ExternalProject_Add(gtest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.8.0
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${gtest_INSTALL_PREFIX}
)
set(gtest_INCLUDE_DIRS "${gtest_INSTALL_PREFIX}/include")
set(gtest_LIBRARIES
    "${gtest_INSTALL_PREFIX}/lib/libgtest${CMAKE_STATIC_LIBRARY_SUFFIX}"
    "${gtest_INSTALL_PREFIX}/lib/libgtest_main${CMAKE_STATIC_LIBRARY_SUFFIX}"
)
add_dependencies(${PROJECT_NAME}-test gtest)
include_directories(${gtest_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}-test ${gtest_LIBRARIES})

find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME}-test ${CMAKE_THREAD_LIBS_INIT})
