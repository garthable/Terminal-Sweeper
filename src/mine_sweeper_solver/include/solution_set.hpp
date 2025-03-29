#pragma once

#include "mine_sweeper_solver.hpp"
#include <vector>
#include <unordered_map>

namespace slvr
{

struct Solution
{
    Solution() : bombCount{0}, numberOfSolutions{1} {}
    BoardBitMap solution;
    mswp::BombCount bombCount;
    uint64_t numberOfSolutions;
};

struct Slice
{

};

class SolutionSet
{
public:
    SolutionSet() :
        m_MinBombs{0},
        m_MaxBombs{0},
        m_StartOffset{0},
        m_EndOffset{0}
    {

    }

    void eliminateSolutions(mswp::FlagsRemaining sumOfMins, mswp::FlagsRemaining sumOfMaxes, mswp::FlagsRemaining minBombs, mswp::FlagsRemaining maxBombs);

    inline void SolutionSet::push(Solution& solution)
    {
        m_Solutions.push_back(solution);
    }
    inline Solution& operator[](size_t i)
    {
        return m_Solutions[i];
    }
    inline size_t size()
    {
        return m_Solutions.size();
    }
    inline void reserve(size_t amount)
    {
        m_Solutions.reserve(amount);
    }
    inline std::vector<Solution>::iterator begin()
    {
        return m_Solutions.begin() + m_StartOffset;
    }
    inline std::vector<Solution>::iterator end()
    {
        return m_Solutions.end() - m_EndOffset;
    }
    inline std::vector<Solution>::const_iterator begin() const
    {
        return m_Solutions.begin() + m_StartOffset;
    }
    inline const std::vector<Solution>::const_iterator end() const
    {
        return m_Solutions.end() - m_EndOffset;
    }

    inline const std::vector<Solution>& solutions() const
    {
        return m_Solutions;
    }
    inline mswp::FlagsRemaining minBombs() const
    {
        return m_MinBombs;
    }
    inline mswp::FlagsRemaining maxBombs() const
    {
        return m_MaxBombs;
    }
    
    inline std::vector<Solution>& solutions()
    {
        return m_Solutions;
    }
    inline mswp::FlagsRemaining& minBombs()
    {
        return m_MinBombs;
    }
    inline mswp::FlagsRemaining& maxBombs()
    {
        return m_MaxBombs;
    }
    
private:
    std::vector<Solution> m_Solutions;
    
    mswp::FlagsRemaining m_MinBombs;
    mswp::FlagsRemaining m_MaxBombs;

    size_t m_StartOffset;
    size_t m_EndOffset;
};

bool shouldCombineSolutionSets(const SolutionSet& solutionSetA, const SolutionSet& solutionSetB, mswp::FlagsRemaining minBombs, mswp::FlagsRemaining maxBombs);
void combineSolutionSets(std::vector<SolutionSet>& outSolutionSets, mswp::FlagsRemaining minBombs, mswp::FlagsRemaining maxBombs);

} // namespace slvr end