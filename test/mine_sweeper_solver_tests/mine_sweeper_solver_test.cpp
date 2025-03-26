#include "gtest/gtest.h"
#include "mine_sweeper.hpp"
#include "mine_sweeper_tile_aliases.hpp"
#include "mine_sweeper_solver_aliases.hpp"
#include "util.hpp"
#include "log.hpp"

#include "mine_sweeper_solver.hpp"

bool compareArray(const slvr::ModifiedBuffer& buffer, const std::initializer_list<mswp::BoardIndex>& initList)
{
    for (mswp::BoardIndex i = 0; i < initList.size(); i++)
    {
        bool matches = false;
        for (mswp::BoardIndex j = 0; j < initList.size(); j++)
        {
            if (buffer[j] == *(initList.begin() + i))
            {
                matches = true;
                break;
            }
        }
        if (!matches)
        {
            for (mswp::BoardIndex i = 0; i < initList.size(); i++)
            {
                std::cout << buffer[i] << ", ";
            }
            std::cout << '\n';
            for (mswp::BoardIndex i = 0; i < initList.size(); i++)
            {
                std::cout << *(initList.begin() + i) << ", ";
            }
            std::cout << '\n';
            LOG_ERROR("Couldnt find " << *(initList.begin() + i));
            return false;
        }
    }
    return true;
}

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

    slvr::MineSweeperSolver mineSweeperSolver(5, 4, 0, board.tileString());

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

    ASSERT_TRUE(compareArray(mineSweeperSolver.modifiedBuffer(), 
    {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19
    }));
    
    for (mswp::BoardIndex i = 0; i < board.size(); i++)
    {
        ASSERT_EQ(mineSweeperSolver[i].adjBombs, 0);
        ASSERT_EQ(mineSweeperSolver[i].bombProb, 0);
        ASSERT_EQ(mineSweeperSolver[i].adjUnknowns, 0);
    }
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

    ASSERT_TRUE(compareArray(mineSweeperSolver.modifiedBuffer(), 
    {
        0, 1, 5, 6
    }));

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

    slvr::SolverInitList solverInitListRepeat =
    {
        B0H0, B2H2, HIDD, HIDD, HIDD,
        B2H2, B5H5, HIDD, HIDD, HIDD,
        HIDD, HIDD, HIDD, HIDD, HIDD,
        HIDD, HIDD, HIDD, HIDD, HIDD
    };
    
    ASSERT_EQ(mineSweeperSolver, solverInitListRepeat);

    // Testing otherside click

    board.click(4, 3);
    mineSweeperSolver.update(board.tileString());

    ASSERT_TRUE(compareArray(mineSweeperSolver.modifiedBuffer(), 
    {
        3, 4, 8, 9, 13, 14, 18, 19
    }));

    slvr::SolverInitList solverInitListOtherSide =
    {
        B0H0, B2H2, HIDD, B2H2, B0H0,
        B2H2, B5H5, HIDD, B3H3, B0H0,
        HIDD, HIDD, HIDD, B2H2, B0H0,
        HIDD, HIDD, HIDD, B1H1, B0H0
    };
    
    ASSERT_EQ(mineSweeperSolver, solverInitListOtherSide);

    // Testing flag

    board.flag(2, 0);
    board.flag(2, 1);
    board.flag(2, 2);
    board.flag(1, 2);
    board.flag(0, 2);
    mineSweeperSolver.update(board.tileString());

    ASSERT_TRUE(compareArray(mineSweeperSolver.modifiedBuffer(), 
    {
        1, 3, 5, 6, 8, 13, 18
    }));

    slvr::SolverInitList solverInitListFlag =
    {
        B0H0, B0H0, BOMB, B0H0, B0H0,
        B0H0, B0H0, BOMB, B0H0, B0H0,
        BOMB, BOMB, BOMB, B0H1, B0H0,
        HIDD, HIDD, HIDD, B0H1, B0H0
    };
    
    ASSERT_EQ(mineSweeperSolver, solverInitListFlag);
}

TEST(SolverTests, update2)
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

    ASSERT_TRUE(compareArray(mineSweeperSolver.modifiedBuffer(), 
    {
        0, 1, 5, 6
    }));

    slvr::SolverInitList solverInitList =
    {
        B0H0, B2H2, HIDD, HIDD, HIDD,
        B2H2, B5H5, HIDD, HIDD, HIDD,
        HIDD, HIDD, HIDD, HIDD, HIDD,
        HIDD, HIDD, HIDD, HIDD, HIDD
    };
    
    ASSERT_EQ(mineSweeperSolver, solverInitList);

    // Testing flag

    board.flag(2, 0);
    board.flag(2, 1);
    board.flag(2, 2);
    board.flag(1, 2);
    board.flag(0, 2);
    mineSweeperSolver.update(board.tileString());

    ASSERT_TRUE(compareArray(mineSweeperSolver.modifiedBuffer(), 
    {
        1, 5, 6
    }));

    slvr::SolverInitList solverInitListFlag =
    {
        B0H0, B0H0, BOMB, HIDD, HIDD,
        B0H0, B0H0, BOMB, HIDD, HIDD,
        BOMB, BOMB, BOMB, HIDD, HIDD,
        HIDD, HIDD, HIDD, HIDD, HIDD
    };
    
    ASSERT_EQ(mineSweeperSolver, solverInitListFlag);


    // Testing otherside click

    board.click(4, 3);
    mineSweeperSolver.update(board.tileString());
    ASSERT_TRUE(compareArray(mineSweeperSolver.modifiedBuffer(), 
    {
        3, 4, 8, 9, 13, 14, 18, 19
    }));

    slvr::SolverInitList solverInitListOtherSide =
    {
        B0H0, B0H0, BOMB, B0H0, B0H0,
        B0H0, B0H0, BOMB, B0H0, B0H0,
        BOMB, BOMB, BOMB, B0H1, B0H0,
        HIDD, HIDD, HIDD, B0H1, B0H0
    };
    
    ASSERT_EQ(mineSweeperSolver, solverInitListOtherSide);
}