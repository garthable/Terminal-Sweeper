#include "solution_set.hpp"
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
    // Removes mins
    for (size_t i = size-1; i != static_cast<size_t>(-1); --i)
    {
        if (m_Solutions[i].bombCount + sumOfMaxes < minBombs)
        {
            m_Solutions.erase(begin() + i);
            ++i;
        }
        else
        {
            m_EndOffset = size - 1 - i;
            break;
        }
    }
    // Removes maxes
    for (size_t i = 0; i < size; ++i)
    {
        if (m_Solutions[i].bombCount + sumOfMins > maxBombs)
        {
            m_Solutions.erase(begin() + i);
            --i;
        }
        else
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
        return 1;
    }
    uint64_t totalAmount = 0; 
    auto begin = outSolutionSets[i].begin();
    auto end = outSolutionSets[i].end();
    for (; begin < end; begin++)
    {
        Solution& solution = *begin;
        mswp::FlagsRemaining newBombCount = bombCount + solution.bombCount;
        // Since MaxBombs go first we need to continue.
        if (newBombCount > maxBombs)
        {
            continue;
        }
        // Since MinBombs go last we know that the rest of the options will not work.
        if (newBombCount < minBombs)
        {
            break;
        }
        solution.numberOfSolutions += combineSolutionSetsReccur(outSolutionSets, minBombs, maxBombs, i + 1, newBombCount);
        totalAmount += solution.numberOfSolutions;
    }
    return totalAmount;
}

void combineSolutionSets(std::vector<SolutionSet>& outSolutionSets, mswp::FlagsRemaining minBombs, mswp::FlagsRemaining maxBombs)
{
    // Removes completely invalid values
    mswp::FlagsRemaining sumOfMins = 0;
    mswp::FlagsRemaining sumOfMaxes = 0;

    // Prepares solutionSets and sums
    for (const SolutionSet& solutionSet : outSolutionSets)
    {
        // Sorts solutionSets by most to least bombs
        std::sort(solutionSet.begin(), solutionSet.end(), 
        [](const Solution& a, const Solution& b) 
        {
            return a.bombCount > b.bombCount;
        });
        sumOfMaxes += solutionSet.maxBombs();
        sumOfMins += solutionSet.minBombs();
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