#include <array>
#include "mine_sweeper_constants.hpp"
#include "mine_sweeper_solver_probs.hpp"
#include "solution_set.hpp"

namespace slvr
{

typedef std::array<double, 9> AdjBombProbs;
typedef std::array<AdjBombProbs, MSWP_MAX_TILES> AdjBombProbsBoard;
typedef std::array<double, MSWP_MAX_TILES> ExpectedValueBoard;

void addSolutionSetsToAdjBombProbs(const std::vector<SolutionSet>& solutionSet, AdjBombProbs& outAdjBombProbs);
void getExpectedValuesBoard(const AdjBombProbs& adjBombProbs, ExpectedValueBoard& outExpectedValueBoard);

} // namespace slvr end