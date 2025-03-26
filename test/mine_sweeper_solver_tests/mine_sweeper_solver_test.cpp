#include "gtest/gtest.h"
#include "mine_sweeper.hpp"
#include "mine_sweeper_tile_aliases.hpp"
#include "mine_sweeper_solver_aliases.hpp"
#include "util.hpp"
#include "log.hpp"

#include "mine_sweeper_solver.hpp"

TEST(SolverTests, update0)
{
    using namespace mswptileconsts;
    using namespace slvrtileconsts;

    mswp::MineSweeper board(5, 
    {
        H0, H0, H0, H0, H0,
        H0, H0, H0, H0, H0,
        H0, H0, H0, H0, H0,
        H0, H0, H0, H0, H0
    });

    LOG_INFO("CREATED BOARD");

    slvr::MineSweeperSolver mineSweeperSolver(5, 4, 0, board.tileString());

    LOG_INFO("CREATED SOLVER");

    for (mswp::BoardIndex i = 0; i < board.size(); i++)
    {
        ASSERT_EQ(mineSweeperSolver[i].adjBombs, -1);
        ASSERT_EQ(mineSweeperSolver[i].adjUnknowns, -1);
        ASSERT_NE(mineSweeperSolver[i].bombProb, mineSweeperSolver[i].bombProb);
    }

    LOG_INFO("TESTED TILES");

    // Test for unknown and bomb counts
    // Test for bomb percentages

    board.click(0, 0);
    mineSweeperSolver.update(board.tileString());

    LOG_INFO("CLICK AND UPDATE");
    
    for (mswp::BoardIndex i = 0; i < board.size(); i++)
    {
        ASSERT_EQ(mineSweeperSolver[i].adjBombs, 0);
        ASSERT_EQ(mineSweeperSolver[i].bombProb, 0);
        ASSERT_EQ(mineSweeperSolver[i].adjUnknowns, 0);
    }

    LOG_INFO("DONE!");
}

TEST(SolverTests, update1)
{
    using namespace mswptileconsts;
    using namespace slvrtileconsts;

    mswp::MineSweeper board(5, 
    {
        H0, H2, B1, H2, H0,
        H2, H5, B2, H3, H0,
        B1, B2, B2, H2, H0,
        H2, H3, H2, H1, H0
    });

    slvr::MineSweeperSolver mineSweeperSolver(5, 4, 5, board.tileString());

    for (mswp::BoardIndex i = 0; i < board.size(); i++)
    {
        ASSERT_EQ(mineSweeperSolver[i].adjBombs, -1);
        ASSERT_EQ(mineSweeperSolver[i].adjUnknowns, -1);
        ASSERT_NE(mineSweeperSolver[i].bombProb, mineSweeperSolver[i].bombProb);
    }

    // Test for unknown and bomb counts
    // Test for bomb percentages

    board.click(0, 0);
    mineSweeperSolver.update(board.tileString());

    slvr::SolverInitList solverInitList =
    {
        B0H0, B2H2, HIDD, HIDD, HIDD,
        B2H2, B5H5, HIDD, HIDD, HIDD,
        HIDD, HIDD, HIDD, HIDD, HIDD,
        HIDD, HIDD, HIDD, HIDD, HIDD
    };
    
    ASSERT_EQ(mineSweeperSolver, solverInitList);

    // Testing repeat input

    board.click(0, 0);
    mineSweeperSolver.update(board.tileString());

    solverInitList =
    {
        B0H0, B2H2, HIDD, HIDD, HIDD,
        B2H2, B5H5, HIDD, HIDD, HIDD,
        HIDD, HIDD, HIDD, HIDD, HIDD,
        HIDD, HIDD, HIDD, HIDD, HIDD
    };
    
    ASSERT_EQ(mineSweeperSolver, solverInitList);

    // Testing repeat input

    board.click(4, 3);
    mineSweeperSolver.update(board.tileString());

    solverInitList =
    {
        B0H0, B2H2, HIDD, B2H2, B0H0,
        B2H2, B5H5, HIDD, B3H3, B0H0,
        HIDD, HIDD, HIDD, B2H2, B0H0,
        B2H2, B3H3, B2H2, B1H1, B0H0
    };
    
    ASSERT_EQ(mineSweeperSolver, solverInitList);

    // Testing flag

    board.flag(2, 0);
    board.flag(2, 1);
    board.flag(2, 2);
    board.flag(1, 2);
    board.flag(0, 2);
    mineSweeperSolver.update(board.tileString());

    solverInitList =
    {
        B0H0, B0H0, BOMB, B0H0, B0H0,
        B0H0, B0H0, BOMB, B0H0, B0H0,
        BOMB, BOMB, BOMB, B0H0, B0H0,
        B0H0, B0H0, B0H0, B0H0, B0H0
    };
    
    ASSERT_EQ(mineSweeperSolver, solverInitList);
}
