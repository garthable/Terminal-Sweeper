set(BENCHMARK_LIBRARIES
    Mine_Sweeper
    benchmark)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/benchmark")
add_executable(Mine_Sweeper_Benchmark mine_sweeper_benchmark.cpp)
target_link_libraries(Mine_Sweeper_Benchmark ${BENCHMARK_LIBRARIES})