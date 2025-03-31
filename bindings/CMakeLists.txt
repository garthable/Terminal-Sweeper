include(FetchContent)
FetchContent_Declare(pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11
    GIT_TAG a34fcdc)

set(BENCHMARK_ENABLE_TESTING OFF)

FetchContent_MakeAvailable(
    pybind11)

pybind11_add_module(mine_sweeper_binding python/mine_sweeper_binding.cpp)
target_link_libraries(mine_sweeper_binding PRIVATE pybind11::module mine_sweeper)

pybind11_add_module(mine_sweeper_solver_binding python/mine_sweeper_solver_binding.cpp)
target_link_libraries(mine_sweeper_solver_binding PRIVATE pybind11::module mine_sweeper mine_sweeper_solver)