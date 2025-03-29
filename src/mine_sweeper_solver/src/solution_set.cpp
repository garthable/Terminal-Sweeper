#include "solution_set.hpp"
#include "log.hpp"
#include <numeric>

namespace slvr
{

bool shouldCombineSolutionSets(const SolutionSet& solutionSetA, const SolutionSet& solutionSetB, mswp::FlagsRemaining minBombs, mswp::FlagsRemaining maxBombs)
{
    uint32_t maxCombined = solutionSetA.maxBombs() + solutionSetB.maxBombs();
    uint32_t minCombined = solutionSetA.minBombs() + solutionSetB.minBombs();
    return maxCombined <= maxBombs || minCombined >= minBombs;
}

void SolutionSet::eliminateSolutions(mswp::FlagsRemaining sumOfMins, mswp::FlagsRemaining sumOfMaxes, mswp::FlagsRemaining minBombs, mswp::FlagsRemaining maxBombs)
{
    sumOfMins -= m_MinBombs;
    sumOfMaxes -= m_MaxBombs;
    size_t size = m_Solutions.size();
    // Removes maxes
    for (size_t i = size-1; i != static_cast<size_t>(-1); --i)
    {
        if (m_Solutions[i].bombCount + sumOfMins <= maxBombs)
        {
            m_EndOffset = size - 1 - i;
            break;
        }
    }
    // Removes mins
    for (size_t i = 0; i < m_Solutions.size(); ++i)
    {
        if (m_Solutions[i].bombCount + sumOfMaxes >= minBombs)
        {
            m_StartOffset = i;
            break;
        }
    }
}

// TODO:
// Optimize this by using slices to combine solution sets with same bomb counts.
// Figure out if knap sack problem is applicable here
uint64_t combineSolutionSetsReccur(std::vector<SolutionSet>& outSolutionSets, mswp::FlagsRemaining minBombs, mswp::FlagsRemaining maxBombs, size_t i = 0, mswp::FlagsRemaining bombCount = 0)
{
    if (i == outSolutionSets.size())
    {
        return static_cast<uint64_t>(bombCount >= minBombs);
    }
    uint64_t totalAmount = 0; 
    auto begin = outSolutionSets[i].begin();
    auto end = outSolutionSets[i].end();
    for (; begin < end; begin++)
    {
        Solution& solution = *begin;
        mswp::FlagsRemaining newBombCount = bombCount + solution.bombCount;
        // Since the rest of the bombs will be greater than this we can break.
        if (newBombCount > maxBombs)
        {
            break;
        }
        uint64_t amount = combineSolutionSetsReccur(outSolutionSets, minBombs, maxBombs, i + 1, newBombCount);
        totalAmount += amount;
        solution.numberOfSolutions += amount;
    }
    return totalAmount;
}

void combineSolutionSets(std::vector<SolutionSet>& outSolutionSets, mswp::FlagsRemaining minBombs, mswp::FlagsRemaining maxBombs)
{
    // Removes completely invalid values
    mswp::FlagsRemaining sumOfMins = 0;
    mswp::FlagsRemaining sumOfMaxes = 0;

    // Prepares solutionSets and sums
    for (SolutionSet& outSolutionSet : outSolutionSets)
    {
        // Sorts solutionSets by least to greatest bombs
        std::sort(outSolutionSet.begin(), outSolutionSet.end(), 
        [](const Solution& a, const Solution& b) 
        {
            return a.bombCount < b.bombCount;
        });
        sumOfMaxes += outSolutionSet.maxBombs();
        sumOfMins += outSolutionSet.minBombs();
    }
    // Removes solutions that will never work.
    for (SolutionSet& outSolutionSet : outSolutionSets)
    {
        outSolutionSet.eliminateSolutions(sumOfMins, sumOfMaxes, minBombs, maxBombs);
    }

    // Combines sets
    combineSolutionSetsReccur(outSolutionSets, minBombs, maxBombs);
}

}