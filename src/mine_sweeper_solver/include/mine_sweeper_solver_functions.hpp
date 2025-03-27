#pragma once

#include "mine_sweeper_solver.hpp"

namespace slvr
{

typedef std::array<mswp::BoardIndex, SLVR_ACTION_BUFFER_SIZE> ActionBuffer;
typedef uint8_t ActionsSize;

struct ActionArray
{
    ActionArray() : actionSize{0} {}
    ActionBuffer actions;
    ActionsSize actionSize;
};

void useActionArrays(ActionArray& outClicks, ActionArray& outFlags, mswp::MineSweeper& outBoard);

void lazySolve(MineSweeperSolver& outSolver, ActionArray& outClicks, ActionArray& outFlags);
void intersectionSolver(MineSweeperSolver& outSolver, ActionArray& outClicks, ActionArray& outFlags);

};