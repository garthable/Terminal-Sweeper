#pragma once

#include "mine_sweeper_solver.hpp"
#include <vector>

namespace slvr
{

struct Solution
{
    BoardBitMap solution;
    mswp::BombCount bombCount;
    uint32_t iteration;
};

class SolutionSet
{
public:
    SolutionSet(mswp::FlagsRemaining remainingBombs, mswp::BoardSize remainingDeepTiles);

    void push(Solution& solution, bool combine);
    
private:
    const mswp::FlagsRemaining m_RemainingBombs;
    const mswp::BoardSize m_RemainingDeepTiles;

    std::vector<Solution> m_Solutions;
    mswp::BombCount m_MinBombs;
    mswp::BombCount m_MaxBombs;
};

} // namespace slvr end