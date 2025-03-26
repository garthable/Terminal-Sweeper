set(BENCHMARK_LIBRARIES
    mine_sweeper
    benchmark)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/benchmark")
add_executable(MineSweeperBenchmark mine_sweeper_benchmark.cpp)
target_link_libraries(MineSweeperBenchmark ${BENCHMARK_LIBRARIES})