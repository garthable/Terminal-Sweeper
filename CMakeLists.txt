cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(MineSweeperSolver VERSION 1.0)

add_library(app STATIC src/app/app.cpp)
add_library(mineSweeper STATIC src/mineSweeper/mineSweeper.cpp)
add_library(mineSweeperSolutionFinder STATIC src/mineSweeperSolutionFinder/mineSweeperSolutionFinder.cpp)
add_library(mineSweeperSolver STATIC src/mineSweeperSolver/mineSweeperSolver.cpp)

add_executable(MineSweeperSolver src/main.cpp)
target_compile_options(MineSweeperSolver PRIVATE -std=c++20 -Wall -Wextra -O3)