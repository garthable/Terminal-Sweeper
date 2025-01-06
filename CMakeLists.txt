cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(MineSweeperSolver VERSION 1.0 LANGUAGES CXX)

add_subdirectory(src/mineSweeper)
add_subdirectory(src/mineSweeperSolver)
add_subdirectory(src/app)

add_executable(MineSweeperSolver src/main.cpp)

target_compile_options(mineSweeperSolver PUBLIC -std=c++20 -Wall -Wextra -O3)
target_compile_options(mineSweeper PUBLIC -std=c++20 -Wall -Wextra -O3)
target_compile_options(app PUBLIC -std=c++20 -Wall -Wextra -O3)
target_compile_options(MineSweeperSolver PUBLIC -std=c++20 -Wall -Wextra -O3)

message(STATUS "${CMAKE_SOURCE_DIR}")

target_link_libraries(MineSweeperSolver PUBLIC app mineSweeper mineSweeperSolver)