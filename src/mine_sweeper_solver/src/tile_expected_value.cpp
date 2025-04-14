#include "tile_expected_value.hpp"
#include "util.hpp"

namespace slvr
{

void addSolutionSetsToAdjBombProbs(const slvr::MineSweeperSolver& slvr, const SolutionSet& solutionSet, AdjBombProbsBoard& outAdjBombProbsBoard)
{
    for (mswp::BoardIndex i = 0; i < slvr.size(); i++)
    {
        std::array<int32_t, 8> adjIndicies;
        util::getAdjIndices(i, slvr.size(), slvr.width(), adjIndicies);
        for (const Solution& solution : solutionSet)
        {
            int8_t adjBombs = 0;
            for (int32_t j : adjIndicies)
            {
                if (j == -1)
                {
                    continue;
                }
                
                adjBombs += solution.solution[j];
            }
            outAdjBombProbsBoard[i][adjBombs] += 1.0;
        }
    }
}

void calcAdjBombProbsForDeepHidden(const slvr::MineSweeperSolver& slvr, const mswp::BombCount deepHiddenBombs, AdjBombProbsBoard& outAdjBombProbsBoard)
{
    uint8_t checkAmount = deepHiddenBombs <= 9u ? deepHiddenBombs : 9u;
}

void normalizeAdjBombProbs(AdjBombProbsBoard& outAdjBombProbsBoard)
{
    for (AdjBombProbs& outAdjBombProbs : outAdjBombProbsBoard)
    {
        double norm = 0.0;
        for (int8_t i = 0; i < 9; i++)
        {
            norm += outAdjBombProbs[i];
        }
        norm = sqrt(norm);
        for (int8_t i = 0; i < 9; i++)
        {
            outAdjBombProbs[i] /= norm;
        }
    }
}

void getExpectedValuesBoard(const AdjBombProbs& adjBombProbs, ExpectedValueBoard& outExpectedValueBoard)
{
    // Copy Solver
    // Try each probability of adj bomb
        // Record how many tiles are uncovered on each step
        // Multiply by probability of it being that adj bomb
        // Add to total amount
    // Set expected amount to this value.
}

} // namespace slvr end