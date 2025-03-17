#pragma once

#include "util.hpp"

namespace app
{

struct Difficulty
{
    enum DifficultyEnum : uint8_t
    {
        BEGINNER     = 1u,
        INTERMEDIATE = 2u,
        EXPERT       = 4u
    };
    static constexpr char beginnerStr[]     = "Beginner    ";
    static constexpr char intermediateStr[] = "Intermediate";
    static constexpr char expertStr[]       = "Expert      ";
    static constexpr size_t strSize = util::getMaxLenStr({beginnerStr, intermediateStr, expertStr})+1;
};

struct FirstClick
{
    enum FirstClickEnum : uint8_t
    {
        _3X3_AREA = 1u,
        _1X1_AREA = 2u,
        _0X0_AREA = 4u
    };
    static constexpr char _3x3AreaStr[] = "3x3 Area";
    static constexpr char _1x1AreaStr[] = "1x1 Area";
    static constexpr char _0x0AreaStr[] = "0x0 Area";
    static constexpr size_t strSize = util::getMaxLenStr({_3x3AreaStr, _1x1AreaStr, _0x0AreaStr})+1;
};

struct AllowedSeeds
{
    enum AllowedSeedsEnum : uint8_t
    {
        ONLY_100_PERCENT_AND_0_PERCENT = 1u,
        HIGHEST_PROB_IS_BOMB           = 2u,
        ALLOW_ALL_SEEDS                = 4u
    };
    static constexpr char only100PercentAnd0PercentStr[] = "Only 100\% and 0\% ";
    static constexpr char highestProbIsBombStr[]         = "Highest \% is Bomb";
    static constexpr char allowAllSeedsStr[]             = "Allow All Seeds  ";
    static constexpr size_t strSize = util::getMaxLenStr({only100PercentAnd0PercentStr, highestProbIsBombStr, allowAllSeedsStr})+1;
};

void runInGUI();
void runInTerminal();

} // app end