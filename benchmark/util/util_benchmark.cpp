#include <array>

#include "benchmark/benchmark.h"
#include "util.hpp"

static void applyFuncToAdjObjects(benchmark::State& state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        std::array<int32_t, 64> array;
        state.ResumeTiming();

        util::applyFuncToAdjObjects<std::array<int32_t, 64>, int32_t>(8, 8, 64, array, 
        [](int32_t& i) 
        {
            i++;
        });
    }
}

BENCHMARK(applyFuncToAdjObjects);

static void isIndexNear(benchmark::State& state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        state.ResumeTiming();

        util::isIndexNear(state.range(0), state.range(1), state.range(2));
    }
}

BENCHMARK(isIndexNear)
    ->Args({8, 8, 1})
    ->Args({8, 8, 7});

BENCHMARK_MAIN();