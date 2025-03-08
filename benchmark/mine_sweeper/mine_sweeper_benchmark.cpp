#include "benchmark/benchmark.h"
#include "mine_sweeper.hpp"
#include "mine_sweeper_constants.hpp"

static void mineSweeperConstructor(benchmark::State& state)
{
    mswp::BoardSeed seed = 0;
    for (auto _ : state)
    {
        mswp::MineSweeper mineSweeper(state.range(0), state.range(1), state.range(2), seed);
        state.PauseTiming();
        seed++;
        state.ResumeTiming();
    }
    state.SetComplexityN(state.range(0)*state.range(1));
}

BENCHMARK(mineSweeperConstructor)
    ->Args({MSWP_BEGINNER_WIDTH, MSWP_BEGINNER_HEIGHT, MSWP_BEGINNER_BOMB_COUNT})
    ->Args({MSWP_INTERMEDIATE_WIDTH, MSWP_INTERMEDIATE_HEIGHT, MSWP_INTERMEDIATE_BOMB_COUNT})
    ->Args({MSWP_EXPERT_WIDTH, MSWP_EXPERT_HEIGHT, MSWP_EXPERT_BOMB_COUNT});

static void mineSweeperFirstClick(benchmark::State& state)
{
    mswp::BoardSeed seed = 0;
    for (auto _ : state)
    {
        state.PauseTiming();
        mswp::MineSweeper mineSweeper(state.range(0), state.range(1), state.range(2), seed);
        seed++;
        state.ResumeTiming();
        mineSweeper.click(1, 1);
    }
}

BENCHMARK(mineSweeperFirstClick)
    ->Args({MSWP_BEGINNER_WIDTH, MSWP_BEGINNER_HEIGHT, MSWP_BEGINNER_BOMB_COUNT})
    ->Args({MSWP_INTERMEDIATE_WIDTH, MSWP_INTERMEDIATE_HEIGHT, MSWP_INTERMEDIATE_BOMB_COUNT})
    ->Args({MSWP_EXPERT_WIDTH, MSWP_EXPERT_HEIGHT, MSWP_EXPERT_BOMB_COUNT});

static void mineSweeperSecondClick(benchmark::State& state)
{
    mswp::BoardSeed seed = 0;
    for (auto _ : state)
    {
        state.PauseTiming();
        mswp::MineSweeper mineSweeper(state.range(0), state.range(1), state.range(2), seed);
        seed++;
        mineSweeper.click(1, 1);
        mswp::BoardXPos x = state.range(0)-2;
        mswp::BoardXPos y = state.range(1)-2;
        state.ResumeTiming();
        mineSweeper.click(x, y);
    }
}

BENCHMARK(mineSweeperSecondClick)
    ->Args({MSWP_BEGINNER_WIDTH, MSWP_BEGINNER_HEIGHT, MSWP_BEGINNER_BOMB_COUNT})
    ->Args({MSWP_INTERMEDIATE_WIDTH, MSWP_INTERMEDIATE_HEIGHT, MSWP_INTERMEDIATE_BOMB_COUNT})
    ->Args({MSWP_EXPERT_WIDTH, MSWP_EXPERT_HEIGHT, MSWP_EXPERT_BOMB_COUNT});

static void mineSweeperFlag(benchmark::State& state)
{
    mswp::MineSweeper mineSweeper(state.range(0), state.range(1), 1, time(0));
    for (auto _ : state)
    {
        mineSweeper.flag(1, 1);
    }
}

BENCHMARK(mineSweeperFlag)
    ->Args({MSWP_BEGINNER_WIDTH, MSWP_BEGINNER_HEIGHT})
    ->Args({MSWP_INTERMEDIATE_WIDTH, MSWP_INTERMEDIATE_HEIGHT})
    ->Args({MSWP_EXPERT_WIDTH, MSWP_EXPERT_HEIGHT});

BENCHMARK_MAIN();