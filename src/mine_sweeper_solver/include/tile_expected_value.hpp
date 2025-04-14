#include <array>
#include "mine_sweeper_constants.hpp"
#include "mine_sweeper_solver_probs.hpp"
#include "solution_set.hpp"

namespace slvr
{

typedef std::array<double, 9> AdjBombProbs;
typedef std::array<AdjBombProbs, MSWP_MAX_TILES> AdjBombProbsBoard;
typedef std::array<double, MSWP_MAX_TILES> ExpectedValueBoard;

void addSolutionSetsToAdjBombProbs(const slvr::MineSweeperSolver& slvr, const SolutionSet& solutionSet, AdjBombProbsBoard& outAdjBombProbsBoard);
void calcAdjBombProbsForDeepHidden(const slvr::MineSweeperSolver& slvr, const mswp::BombCount deepHiddenBombs, AdjBombProbsBoard& outAdjBombProbsBoard);
void normalizeAdjBombProbs(AdjBombProbsBoard& outAdjBombProbsBoard);
void getExpectedValuesBoard(const AdjBombProbs& adjBombProbs, ExpectedValueBoard& outExpectedValueBoard);

} // namespace slvr end