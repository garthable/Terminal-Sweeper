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
project(MineSweeperSolver VERSION 0.1.0)

set(CMAKE_CXX_STANDARD, 20)
set(CMAKE_C_STANDARD, 99)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    message(STATUS "Clang detected, adding compile flags")
    add_compile_options(-Wall -Wextra -Wshadow -Wpointer-arith -Wcast-align -Wcast-qual -O3)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(STATUS "GCC detected, adding compile flags")
    add_compile_options(-Wall -Wextra -Wundef -Wshadow -Wpointer-arith -Wcast-align -Wcast-qual -O3)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
    message(WARNING "Intel Compiler not tested")
    message(STATUS "Intel detected, adding compile flags")
    add_compile_options()
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    message(STATUS "MSVC detected, adding compile flags")
    add_compile_options()
endif()

message(STATUS "${CMAKE_GENERATOR}")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)
add_subdirectory(test)

add_subdirectory(benchmark)
