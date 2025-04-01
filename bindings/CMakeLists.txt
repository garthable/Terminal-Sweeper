include(FetchContent)
FetchContent_Declare(pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11
    GIT_TAG a34fcdc)

FetchContent_MakeAvailable(
    pybind11)

find_package(Python3 REQUIRED COMPONENTS Development)

pybind11_add_module(MineSweeper python/mine_sweeper_binding.cpp)
target_link_libraries(MineSweeper PRIVATE Python3::Python pybind11::module mine_sweeper mine_sweeper_solver)

set_target_properties(MineSweeper PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bindings
    PREFIX ""  # Remove the "lib" prefix if you don't want it
    SUFFIX ".so"  # Set the file extension to .so instead of .cpython-xyz.so
)

add_custom_target(MineSweeperCopyPython ALL
	COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/test.py
    ${CMAKE_CURRENT_BINARY_DIR}/test.py
) 