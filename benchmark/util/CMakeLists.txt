set(BENCHMARK_LIBRARIES
    util
    benchmark)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/benchmark")
add_executable(UtilBenchmark util_benchmark.cpp)
target_link_libraries(UtilBenchmark ${BENCHMARK_LIBRARIES})