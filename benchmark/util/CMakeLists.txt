set(BENCHMARK_LIBRARIES
    Util
    benchmark)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/benchmark")
add_executable(Util_Benchmark util_benchmark.cpp)
target_link_libraries(Util_Benchmark ${BENCHMARK_LIBRARIES})