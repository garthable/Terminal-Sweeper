#pragma once

#include "mine_sweeper_solver.hpp"
#include <algorithm>

namespace slvr
{

typedef std::array<mswp::BoardIndex, SLVR_ACTION_BUFFER_SIZE> ActionBuffer;
typedef uint8_t ActionsSize;

class ActionArray
{
public:
    ActionArray() : m_Size{0} {}

    inline void push(mswp::BoardIndex i)
    {
        m_Actions[m_Size] = i;
        m_Size++;
    }

    inline bool in(mswp::BoardIndex i) const
    {
        for (ActionsSize j = 0; j < m_Size; j++)
        {
            if (m_Actions[j] == i)
            {
                return true;
            }
        }
        return false;
    }

    inline void remove(mswp::BoardIndex item)
    {
        if (!in(item))
        {
            return;
        }
        std::remove(m_Actions.begin(), m_Actions.end(), item);
        m_Size--;
    }

    inline void update(const mswp::TileString& tileString)
    {
        for (mswp::TileStringIndex i = 0; i < tileString.size(); i++)
        {
            if (tileString[i] != mswp::TileChar::HIDDEN)
            {
                remove(i);
            }
        }
    }

    inline void reset()
    {
        m_Size = 0;
    }

    inline mswp::BoardIndex operator[](ActionsSize i) const
    {
        return m_Actions[i];
    }

    inline mswp::BoardIndex& operator[](ActionsSize i)
    {
        return m_Actions[i];
    }

    inline ActionBuffer::iterator begin()
    {
        return m_Actions.begin();
    }

    inline ActionBuffer::iterator end()
    {
        return m_Actions.end();
    }

    inline ActionBuffer::const_iterator begin() const
    {
        return m_Actions.begin();
    }

    inline ActionBuffer::const_iterator end() const
    {
        return m_Actions.end();
    }

    inline ActionsSize size() const
    {
        return m_Size;
    }

    inline const ActionBuffer& actions() const
    {
        return m_Actions;
    }

private:
    ActionBuffer m_Actions;
    ActionsSize m_Size;
};

void useActionArrays(ActionArray& outClicks, ActionArray& outFlags, mswp::MineSweeper& outBoard);

void lazySolve(MineSweeperSolver& outSolver, ActionArray& outClicks, ActionArray& outFlags);
void intersectionSolver(MineSweeperSolver& outSolver, ActionArray& outClicks, ActionArray& outFlags);

void getRecommendedActions(MineSweeperSolver& outSolver, ActionArray& outClicks, ActionArray& outFlags);

}