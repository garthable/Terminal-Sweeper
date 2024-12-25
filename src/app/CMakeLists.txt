add_compile_definitions(SETTINGSFILE="${CMAKE_SOURCE_DIR}/doc/settings.txt")
message(STATUS "Settings path: ${CMAKE_SOURCE_DIR}/doc/settings.txt")

add_compile_definitions(TESTDIRECTORY="${CMAKE_SOURCE_DIR}/tests")
message(STATUS "Test path: ${CMAKE_SOURCE_DIR}/tests")

add_library(app STATIC src/app.cpp)
target_include_directories(app PUBLIC include)

target_link_libraries(app PUBLIC mineSweeper mineSweeperSolver)