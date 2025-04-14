#pragma once

#include "mine_sweeper_solver.hpp"
#include <vector>
#include <unordered_map>

#include "log.hpp"

namespace slvr
{

struct Solution
{
    Solution() : bombCount{0}, numberOfSolutions{0} {}
    Solution(mswp::FlagsRemaining bombCount, uint64_t numberOfSolutions) : bombCount{bombCount}, numberOfSolutions{numberOfSolutions} {}
    Solution(const BoardBitMap& boardBitMap, mswp::FlagsRemaining bombCount) : solution{boardBitMap}, bombCount{bombCount}, numberOfSolutions{0} {}
    BoardBitMap solution;
    mswp::FlagsRemaining bombCount;
    uint64_t numberOfSolutions;
};

class SolutionSet
{
public:
    SolutionSet() :
        m_MinBombs{INT8_MAX},
        m_MaxBombs{0},
        m_StartOffset{0},
        m_EndOffset{0}
    {

    }

    void eliminateSolutions(mswp::FlagsRemaining sumOfMins, mswp::FlagsRemaining sumOfMaxes, mswp::FlagsRemaining minBombs, mswp::FlagsRemaining maxBombs);

    inline void push(const Solution& solution)
    {
        m_MaxBombs = std::max(static_cast<int32_t>(m_MaxBombs), static_cast<int32_t>(solution.bombCount));
        m_MinBombs = std::min(static_cast<int32_t>(m_MinBombs), static_cast<int32_t>(solution.bombCount));
        m_Solutions.push_back(solution);
    }
    inline void push(Solution&& solution)
    {
        m_MaxBombs = std::max(static_cast<int32_t>(m_MaxBombs), static_cast<int32_t>(solution.bombCount));
        m_MinBombs = std::min(static_cast<int32_t>(m_MinBombs), static_cast<int32_t>(solution.bombCount));
        m_Solutions.emplace_back(solution);
    }
    inline Solution& operator[](size_t i)
    {
        return m_Solutions[i + m_StartOffset];
    }
    inline const Solution& operator[](size_t i) const
    {
        return m_Solutions[i + m_StartOffset];
    }
    inline size_t size() const
    {
        return m_Solutions.size() - m_EndOffset;
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

bool shouldCombineSolutionSets(const std::vector<SolutionSet>& solutionSets, mswp::FlagsRemaining minBombs, mswp::FlagsRemaining maxBombs);
void combineSolutionSets(std::vector<SolutionSet>& outSolutionSets, mswp::FlagsRemaining minBombs, mswp::FlagsRemaining maxBombs);

} // namespace slvr end