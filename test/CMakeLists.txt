# Copyright 2025 Dalton Prokosch

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GOOGLE_TEST_VERSION 1.15.2)
set(TEST_LIBRARIES
    Util
    Mine_Sweeper
    App
    gtest_main
)
set(TEST_SOURCE
    mine_sweeper_tests/mine_sweeper_test.cpp
    mine_sweeper_tests/mine_sweeper_tile_test.cpp
)

enable_testing()

# Installs google test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v${GOOGLE_TEST_VERSION}.zip 
    FIND_PACKAGE_ARGS ${GOOGLE_TEST_VERSION}
)
FetchContent_MakeAvailable(googletest)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
add_executable(Mine_Sweeper_Test ${TEST_SOURCE})
target_link_libraries(Mine_Sweeper_Test ${TEST_LIBRARIES})