#include "gtest/gtest.h"
#include "mine_sweeper.hpp"
#include "mine_sweeper_tile_aliases.hpp"
#include "mine_sweeper_solver_aliases.hpp"
#include "util.hpp"
#include "log.hpp"

#include "mine_sweeper_solver.hpp"
#include "mine_sweeper_solver_functions.hpp"
#include "mine_sweeper_solver_probs.hpp"
#include "solution_set.hpp"

bool compareArray(const slvr::TilesWithAdjBombBuffer& buffer, const std::initializer_list<mswp::BoardIndex>& initList)
{
    for (size_t i = 0; i < initList.size(); i++)
    {
        bool matches = false;
        for (size_t j = 0; j < initList.size(); j++)
        {
            if (buffer[j] == *(initList.begin() + i))
            {
                matches = true;
                break;
            }
        }
        if (!matches)
        {
            for (size_t j = 0; j < initList.size(); j++)
            {
                std::cout << buffer[j] << ", ";
            }
            std::cout << '\n';
            for (size_t j = 0; j < initList.size(); j++)
            {
                std::cout << *(initList.begin() + j) << ", ";
            }
            std::cout << '\n';
            LOG_ERROR("Couldnt find " << *(initList.begin() + i));
            return false;
        }
    }
    return true;
}

bool compareArray(const slvr::ActionArray& buffer, const std::initializer_list<mswp::BoardIndex>& initList)
{
    size_t actionSize = buffer.size();
    if (initList.size() != actionSize)
    {
        LOG_ERROR("Sizes done match! " << initList.size() << " != " << actionSize);
        return false;
    }
    for (size_t i = 0; i < initList.size(); i++)
    {
        bool matches = false;
        for (size_t j = 0; j < initList.size(); j++)
        {
            if (buffer[j] == *(initList.begin() + i))
            {
                matches = true;
                break;
            }
        }
        if (!matches)
        {
            LOG_ERROR("Couldnt find " << *(initList.begin() + i));
            return false;
        }
    }
    return true;
}

bool compareArray(const slvr::group::TileGroup& buffer, const std::initializer_list<mswp::BoardIndex>& initList)
{
    size_t actionSize = buffer.size;
    if (initList.size() != actionSize)
    {
        LOG_ERROR("Sizes done match! " << initList.size() << " != " << actionSize);
        return false;
    }
    for (size_t i = 0; i < initList.size(); i++)
    {
        bool matches = false;
        for (size_t j = 0; j < initList.size(); j++)
        {
            if (buffer.tiles[j].tileIndex == *(initList.begin() + i))
            {
                matches = true;
                break;
            }
        }
        if (!matches)
        {
            LOG_ERROR("Couldnt find " << *(initList.begin() + i));
            return false;
        }
    }
    return true;
}

bool compareArray(const std::array<mswp::BoardIndex, 8> buffer, const std::initializer_list<mswp::BoardIndex>& initList)
{
    for (size_t i = 0; i < initList.size(); i++)
    {
        bool matches = false;
        for (size_t j = 0; j < initList.size(); j++)
        {
            if (buffer[j] == *(initList.begin() + i))
            {
                matches = true;
                break;
            }
        }
        if (!matches)
        {
            LOG_ERROR("Couldnt find " << *(initList.begin() + i));
            return false;
        }
    }
    return true;
}

// TEST(Update, 0)
// {
//     using namespace mswptileconsts;
//     using namespace slvrtileconsts;

//     mswp::MineSweeper board(5, 
//     {
//         H0, H0, H0, H0, H0,
//         H0, H0, H0, H0, H0,
//         H0, H0, H0, H0, H0,
//         H0, H0, H0, H0, H0
//     });

//     slvr::MineSweeperSolver mineSweeperSolver(board);

//     for (mswp::BoardIndex i = 0; i < board.size(); i++)
//     {
//         ASSERT_EQ(mineSweeperSolver[i].adjBombs, -1);
//         ASSERT_EQ(mineSweeperSolver[i].adjUnknowns, -1);
//         ASSERT_NE(mineSweeperSolver[i].bombProb, mineSweeperSolver[i].bombProb);
//     }

//     // Test for unknown and bomb counts
//     // Test for bomb percentages

//     board.click(0, 0);
//     mineSweeperSolver.update(board.tileString());

//     ASSERT_TRUE(compareArray(mineSweeperSolver.tilesWithAdjBombBuffer(), 
//     {
//         0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19
//     }));
    
//     for (mswp::BoardIndex i = 0; i < board.size(); i++)
//     {
//         ASSERT_EQ(mineSweeperSolver[i].adjBombs, 0);
//         ASSERT_EQ(mineSweeperSolver[i].bombProb, 0);
//         ASSERT_EQ(mineSweeperSolver[i].adjUnknowns, 0);
//     }
// }

// TEST(Update, 1)
// {
//     using namespace mswptileconsts;
//     using namespace slvrtileconsts;

//     mswp::MineSweeper board(5, 
//     {
//         H0, H2, B1, H2, H0,
//         H2, H5, B2, H3, H0,
//         B1, B2, B2, H2, H0,
//         H2, H3, H2, H1, H0
//     });

//     slvr::MineSweeperSolver mineSweeperSolver(board);

//     for (mswp::BoardIndex i = 0; i < board.size(); i++)
//     {
//         ASSERT_EQ(mineSweeperSolver[i].adjBombs, -1);
//         ASSERT_EQ(mineSweeperSolver[i].adjUnknowns, -1);
//         ASSERT_NE(mineSweeperSolver[i].bombProb, mineSweeperSolver[i].bombProb);
//     }

//     // Test for unknown and bomb counts
//     // Test for bomb percentages

//     board.click(0, 0);
//     mineSweeperSolver.update(board.tileString());

//     ASSERT_TRUE(compareArray(mineSweeperSolver.tilesWithAdjBombBuffer(), 
//     {
//         0, 1, 5, 6
//     }));

//     slvr::SolverInitList solverInitList =
//     {
//         B0H0, B2H2, HIDD, HIDD, HIDD,
//         B2H2, B5H5, HIDD, HIDD, HIDD,
//         HIDD, HIDD, HIDD, HIDD, HIDD,
//         HIDD, HIDD, HIDD, HIDD, HIDD
//     };
    
//     ASSERT_EQ(mineSweeperSolver, solverInitList);

//     // Testing repeat input

//     board.click(0, 0);
//     mineSweeperSolver.update(board.tileString());

//     slvr::SolverInitList solverInitListRepeat =
//     {
//         B0H0, B2H2, HIDD, HIDD, HIDD,
//         B2H2, B5H5, HIDD, HIDD, HIDD,
//         HIDD, HIDD, HIDD, HIDD, HIDD,
//         HIDD, HIDD, HIDD, HIDD, HIDD
//     };
    
//     ASSERT_EQ(mineSweeperSolver, solverInitListRepeat);

//     // Testing otherside click

//     board.click(4, 3);
//     mineSweeperSolver.update(board.tileString());

//     ASSERT_TRUE(compareArray(mineSweeperSolver.tilesWithAdjBombBuffer(), 
//     {
//         3, 4, 8, 9, 13, 14, 18, 19
//     }));

//     slvr::SolverInitList solverInitListOtherSide =
//     {
//         B0H0, B2H2, HIDD, B2H2, B0H0,
//         B2H2, B5H5, HIDD, B3H3, B0H0,
//         HIDD, HIDD, HIDD, B2H2, B0H0,
//         HIDD, HIDD, HIDD, B1H1, B0H0
//     };
    
//     ASSERT_EQ(mineSweeperSolver, solverInitListOtherSide);

//     // Testing flag

//     board.flag(2, 0);
//     board.flag(2, 1);
//     board.flag(2, 2);
//     board.flag(1, 2);
//     board.flag(0, 2);
//     mineSweeperSolver.update(board.tileString());

//     ASSERT_TRUE(compareArray(mineSweeperSolver.tilesWithAdjBombBuffer(), 
//     {
//         1, 3, 5, 6, 8, 13, 18
//     }));

//     slvr::SolverInitList solverInitListFlag =
//     {
//         B0H0, B0H0, BOMB, B0H0, B0H0,
//         B0H0, B0H0, BOMB, B0H0, B0H0,
//         BOMB, BOMB, BOMB, B0H1, B0H0,
//         HIDD, HIDD, HIDD, B0H1, B0H0
//     };
    
//     ASSERT_EQ(mineSweeperSolver, solverInitListFlag);
// }

// TEST(Update, 2)
// {
//     using namespace mswptileconsts;
//     using namespace slvrtileconsts;

//     mswp::MineSweeper board(5, 
//     {
//         H0, H2, B1, H2, H0,
//         H2, H5, B2, H3, H0,
//         B1, B2, B2, H2, H0,
//         H2, H3, H2, H1, H0
//     });

//     slvr::MineSweeperSolver mineSweeperSolver(board);

//     for (mswp::BoardIndex i = 0; i < board.size(); i++)
//     {
//         ASSERT_EQ(mineSweeperSolver[i].adjBombs, -1);
//         ASSERT_EQ(mineSweeperSolver[i].adjUnknowns, -1);
//         ASSERT_NE(mineSweeperSolver[i].bombProb, mineSweeperSolver[i].bombProb);
//     }

//     // Test for unknown and bomb counts
//     // Test for bomb percentages

//     board.click(0, 0);
//     mineSweeperSolver.update(board.tileString());

//     ASSERT_TRUE(compareArray(mineSweeperSolver.tilesWithAdjBombBuffer(), 
//     {
//         0, 1, 5, 6
//     }));

//     slvr::SolverInitList solverInitList =
//     {
//         B0H0, B2H2, HIDD, HIDD, HIDD,
//         B2H2, B5H5, HIDD, HIDD, HIDD,
//         HIDD, HIDD, HIDD, HIDD, HIDD,
//         HIDD, HIDD, HIDD, HIDD, HIDD
//     };
    
//     ASSERT_EQ(mineSweeperSolver, solverInitList);

//     // Testing flag

//     board.flag(2, 0);
//     board.flag(2, 1);
//     board.flag(2, 2);
//     board.flag(1, 2);
//     board.flag(0, 2);
//     mineSweeperSolver.update(board.tileString());

//     ASSERT_TRUE(compareArray(mineSweeperSolver.tilesWithAdjBombBuffer(), 
//     {
//         1, 5, 6
//     }));

//     slvr::SolverInitList solverInitListFlag =
//     {
//         B0H0, B0H0, BOMB, HIDD, HIDD,
//         B0H0, B0H0, BOMB, HIDD, HIDD,
//         BOMB, BOMB, BOMB, HIDD, HIDD,
//         HIDD, HIDD, HIDD, HIDD, HIDD
//     };
    
//     ASSERT_EQ(mineSweeperSolver, solverInitListFlag);


//     // Testing otherside click

//     board.click(4, 3);
//     mineSweeperSolver.update(board.tileString());
//     ASSERT_TRUE(compareArray(mineSweeperSolver.tilesWithAdjBombBuffer(), 
//     {
//         3, 4, 8, 9, 13, 14, 18, 19
//     }));

//     slvr::SolverInitList solverInitListOtherSide =
//     {
//         B0H0, B0H0, BOMB, B0H0, B0H0,
//         B0H0, B0H0, BOMB, B0H0, B0H0,
//         BOMB, BOMB, BOMB, B0H1, B0H0,
//         HIDD, HIDD, HIDD, B0H1, B0H0
//     };
    
//     ASSERT_EQ(mineSweeperSolver, solverInitListOtherSide);
// }

TEST(LazySolver, 0)
{
    using namespace mswptileconsts;
    using namespace slvrtileconsts;

    mswp::MineSweeper board(5, 
    {
        H0, H0, H0, H0, H0,
        H0, H1, H2, H2, H1,
        H0, H2, B2, B1, H1,
        H0, H2, B1, H3, H1
    });

    slvr::MineSweeperSolver solver(board);

    board.click(0, 0);
    solver.update(board.tileString());

    slvr::ActionArray clicks;
    slvr::ActionArray flags;
    slvr::lazySolve(solver, clicks, flags);

    ASSERT_TRUE(compareArray(flags, {12, 13, 17}));
}

TEST(LazySolver, 1)
{
    using namespace mswptileconsts;
    using namespace slvrtileconsts;

    mswp::MineSweeper board(5, 
    {
        H0, H2, B0, H2, H0,
        H1, H4, B0, H3, H0,
        B0, H2, B0, H2, H0,
        H1, H2, H1, H1, H0
    });

    slvr::MineSweeperSolver solver(board);

    board.click(0, 0);
    solver.update(board.tileString());
    board.flag(2, 0);
    board.flag(2, 1);
    board.flag(2, 2);
    board.flag(0, 2);
    solver.update(board.tileString());

    slvr::ActionArray clicks;
    slvr::ActionArray flags;
    slvr::lazySolve(solver, clicks, flags);

    ASSERT_TRUE(compareArray(clicks, {11}));
}

TEST(LazySolver, 2)
{
    using namespace mswptileconsts;
    using namespace slvrtileconsts;

    mswp::MineSweeper board(5, 
    {
        H0, H0, H2, B0, H2,
        H2, H3, H4, B0, H2,
        B1, B2, B1, H2, H1,
        H2, H3, H2, H1, H0
    });

    slvr::MineSweeperSolver solver(board);

    board.click(0, 0);

    slvr::ActionArray clicks;
    slvr::ActionArray flags;

    solver.update(board.tileString());
    slvr::lazySolve(solver, clicks, flags);

    ASSERT_TRUE(compareArray(flags, {3, 8, 10, 11, 12}));

    slvr::useActionArrays(clicks, flags, board);
    solver.update(board.tileString());
    slvr::lazySolve(solver, clicks, flags);

    ASSERT_TRUE(compareArray(clicks, {13}));

    slvr::useActionArrays(clicks, flags, board);
    solver.update(board.tileString());
    slvr::lazySolve(solver, clicks, flags);

    ASSERT_TRUE(compareArray(clicks, {9, 14, 19, 18, 17}));

    slvr::useActionArrays(clicks, flags, board);
    solver.update(board.tileString());
    slvr::lazySolve(solver, clicks, flags);

    ASSERT_TRUE(compareArray(clicks, {16, 4}));

    slvr::useActionArrays(clicks, flags, board);
    solver.update(board.tileString());
    slvr::lazySolve(solver, clicks, flags);

    ASSERT_TRUE(compareArray(clicks, {15}));
}

TEST(IntersectionSolver, 0)
{
    using namespace mswptileconsts;
    using namespace slvrtileconsts;

    mswp::MineSweeper board(5, 
    {
        H0, H0, H1, B0, H1,
        H1, H1, H1, H1, H1,
        B0, H1, H0, H0, H0,
        H1, H1, H0, H0, H0
    });

    slvr::MineSweeperSolver solver(board);

    board.click(0, 0);

    solver.update(board.tileString());
    slvr::ActionArray clicks, flags;
    slvr::intersectionSolver(solver, clicks, flags);

    ASSERT_TRUE(compareArray(clicks, {11, 12, 13}));
    ASSERT_TRUE(compareArray(flags, {}));
}

TEST(IntersectionSolver, 1)
{
    using namespace mswptileconsts;
    using namespace slvrtileconsts;

    mswp::MineSweeper board(5, 
    {
        H0, H0, H2, B1, H2,
        H1, H1, H3, B2, H3,
        B0, H1, H2, B1, H2,
        H1, H1, H1, H1, H1
    });

    slvr::MineSweeperSolver solver(board);

    board.click(0, 0);

    solver.update(board.tileString());
    slvr::ActionArray clicks, flags;
    slvr::intersectionSolver(solver, clicks, flags);

    ASSERT_TRUE(compareArray(clicks, {12}));
    ASSERT_TRUE(compareArray(flags, {3, 8}));
}

TEST(Grouping, 0)
{
    using namespace mswptileconsts;
    using namespace slvrtileconsts;

    mswp::MineSweeper board(5, 
    {
        V1, V1, V2, V1, V1,
        V2, B1, V4, B1, V2,
        V2, B1, V4, B1, V2,
        V1, V1, V2, V1, V1
    });

    slvr::MineSweeperSolver solver(board);

    slvr::BoardBitMap visited;
    slvr::group::TileGroup tileGroup;
    slvr::group::findHiddenTiles(0, solver, visited, tileGroup);

    ASSERT_TRUE(compareArray(tileGroup, {0, 1, 2, 3, 4, 5, 7, 9, 10, 12, 14, 15, 16, 17, 18, 19}));
}

TEST(Grouping, 1)
{
    using namespace mswptileconsts;
    using namespace slvrtileconsts;

    mswp::MineSweeper board(5, 
    {
        V1, V1, B1, V1, V1,
        V1, B1, B1, B1, V1,
        V1, B1, B1, B1, V1,
        V1, V1, B1, V1, V1
    });

    slvr::MineSweeperSolver solver(board);

    slvr::BoardBitMap visited;
    slvr::group::TileGroup tileGroup;
    slvr::group::findHiddenTiles(0, solver, visited, tileGroup);

    ASSERT_TRUE(compareArray(tileGroup, {0, 1, 5, 10, 15, 16, 3, 4, 9, 14, 19, 18}));
}

TEST(Grouping, 2)
{
    using namespace mswptileconsts;
    using namespace slvrtileconsts;

    mswp::MineSweeper board(5, 
    {
        V1, V1, B1, B1, V1,
        V1, B1, B1, B1, V1,
        V1, B1, B1, B1, V1,
        V1, B1, B1, V1, V1
    });

    slvr::MineSweeperSolver solver(board);

    slvr::BoardBitMap visited;
    slvr::group::TileGroup tileGroup;
    slvr::group::findHiddenTiles(0, solver, visited, tileGroup);

    ASSERT_TRUE(compareArray(tileGroup, {0, 1, 5, 10, 15}));
}

TEST(Grouping, 3)
{
    using namespace mswptileconsts;
    using namespace slvrtileconsts;

    mswp::MineSweeper board(5, 
    {
        V1, V1, B1, V0, V1,
        V1, B1, B1, V0, V1,
        V1, B1, V0, V0, V1,
        V1, B1, V0, V1, V1
    });

    slvr::MineSweeperSolver solver(board);

    slvr::BoardBitMap visited;
    slvr::group::TileGroup tileGroup;
    slvr::group::findHiddenTiles(0, solver, visited, tileGroup);

    ASSERT_TRUE(compareArray(tileGroup, {0, 1, 5, 10, 15}));
}

TEST(Sorting, 0)
{
    using namespace mswptileconsts;
    using namespace slvrtileconsts;

    mswp::MineSweeper board(3, 
    {
        V1, V1, V2,
        H1, H1, H1
    });

    slvr::MineSweeperSolver solver(board);

    slvr::group::TileGroup tileGroup({0, 1, 2});
    slvr::sortByCombinationCount(solver, tileGroup);

    ASSERT_EQ(tileGroup.tiles[0].tileIndex, 1);
    ASSERT_EQ(tileGroup.tiles[0].size, 3);
    ASSERT_TRUE(compareArray(tileGroup.tiles[0].adjTiles, {3, 4, 5}));
}

TEST(Sorting, 1)
{
    using namespace mswptileconsts;
    using namespace slvrtileconsts;

    mswp::MineSweeper board(5, 
    {
        H1, V1, H1, V2, H1,
        H1, H1, H1, H1, H1
    });

    slvr::MineSweeperSolver solver(board);

    slvr::group::TileGroup tileGroup({1, 3});
    slvr::sortByCombinationCount(solver, tileGroup);

    ASSERT_EQ(tileGroup.tiles[0].tileIndex, 3);
    ASSERT_EQ(tileGroup.tiles[1].tileIndex, 1);
    ASSERT_EQ(tileGroup.tiles[0].size, 5);
    ASSERT_EQ(tileGroup.tiles[1].size, 3);
    ASSERT_TRUE(compareArray(tileGroup.tiles[0].adjTiles, {2, 7, 8, 9, 4}));
    ASSERT_TRUE(compareArray(tileGroup.tiles[1].adjTiles, {0, 5, 6}));
}

TEST(CombineSolutionSets, 0)
{
    slvr::SolutionSet solutionSetA;
    solutionSetA.push(slvr::Solution(0, 0));
    solutionSetA.push(slvr::Solution(0, 0));
    slvr::SolutionSet solutionSetB;
    solutionSetB.push(slvr::Solution(0, 0));
    slvr::SolutionSet solutionSetC;
    solutionSetC.push(slvr::Solution(0, 0));
    solutionSetC.push(slvr::Solution(0, 0));
    solutionSetC.push(slvr::Solution(0, 0));

    std::vector<slvr::SolutionSet> solutionSets = {solutionSetA, solutionSetB, solutionSetC};

    slvr::combineSolutionSets(solutionSets, 0, 5);

    ASSERT_EQ(solutionSets[0][0].numberOfSolutions, 3);
    ASSERT_EQ(solutionSets[0][1].numberOfSolutions, 3);

    ASSERT_EQ(solutionSets[1][0].numberOfSolutions, 6);

    ASSERT_EQ(solutionSets[2][0].numberOfSolutions, 2);
    ASSERT_EQ(solutionSets[2][1].numberOfSolutions, 2);
    ASSERT_EQ(solutionSets[2][2].numberOfSolutions, 2);
}

TEST(CombineSolutionSets, 1)
{
    slvr::SolutionSet solutionSetA;
    solutionSetA.push(slvr::Solution(5, 0)); // Eliminated
    solutionSetA.push(slvr::Solution(2, 0));
    solutionSetA.push(slvr::Solution(3, 0));
    slvr::SolutionSet solutionSetB;
    solutionSetB.push(slvr::Solution(3, 0)); // Eliminated
    solutionSetB.push(slvr::Solution(1, 0));
    solutionSetB.push(slvr::Solution(4, 0)); // Eliminated

    std::vector<slvr::SolutionSet> solutionSets = {solutionSetA, solutionSetB};

    slvr::combineSolutionSets(solutionSets, 2, 4);

    ASSERT_EQ(solutionSets[0][0].bombCount, 2);
    ASSERT_EQ(solutionSets[1][0].bombCount, 1);

    ASSERT_EQ(solutionSets[0][0].numberOfSolutions, 1);
    ASSERT_EQ(solutionSets[0][1].numberOfSolutions, 1);

    ASSERT_EQ(solutionSets[1][0].numberOfSolutions, 2);
}

TEST(CombineSolutionSets, 2)
{
    slvr::SolutionSet solutionSetA;
    solutionSetA.push(slvr::Solution(0, 0)); // Eliminated
    solutionSetA.push(slvr::Solution(2, 0));
    solutionSetA.push(slvr::Solution(3, 0));
    slvr::SolutionSet solutionSetB;
    solutionSetB.push(slvr::Solution(1, 0));

    std::vector<slvr::SolutionSet> solutionSets = {solutionSetA, solutionSetB};

    slvr::combineSolutionSets(solutionSets, 2, 10);

    ASSERT_EQ(solutionSets[0][0].numberOfSolutions, 1);
    ASSERT_EQ(solutionSets[0][1].numberOfSolutions, 1);

    ASSERT_EQ(solutionSets[1][0].numberOfSolutions, 2);
}

TEST(CombineSolutionSets, 3)
{
    slvr::SolutionSet solutionSetA;
    solutionSetA.push(slvr::Solution(0, 0));
    solutionSetA.push(slvr::Solution(1, 0));
    slvr::SolutionSet solutionSetB;
    solutionSetB.push(slvr::Solution(0, 0));
    slvr::SolutionSet solutionSetC;
    solutionSetC.push(slvr::Solution(0, 0));
    solutionSetC.push(slvr::Solution(0, 0));
    solutionSetC.push(slvr::Solution(1, 0));
    std::vector<slvr::SolutionSet> solutionSets = {solutionSetA, solutionSetB, solutionSetC};

    slvr::combineSolutionSets(solutionSets, 0, 1);

    ASSERT_EQ(solutionSets[0][0].numberOfSolutions, 3);
    ASSERT_EQ(solutionSets[0][1].numberOfSolutions, 2);

    ASSERT_EQ(solutionSets[1][0].numberOfSolutions, 5);

    ASSERT_EQ(solutionSets[2][0].numberOfSolutions, 2);
    ASSERT_EQ(solutionSets[2][1].numberOfSolutions, 2);
    ASSERT_EQ(solutionSets[2][2].numberOfSolutions, 1);
}

TEST(CombineSolutionSets, 4)
{
    slvr::SolutionSet solutionSetA;
    solutionSetA.push(slvr::Solution(0, 0)); // 3
    solutionSetA.push(slvr::Solution(1, 0)); // 1
    slvr::SolutionSet solutionSetB;
    solutionSetB.push(slvr::Solution(0, 0)); // 4
    slvr::SolutionSet solutionSetC;
    solutionSetC.push(slvr::Solution(0, 0)); // 2
    solutionSetC.push(slvr::Solution(0, 0)); // 1
    solutionSetC.push(slvr::Solution(1, 0)); // 1
    std::vector<slvr::SolutionSet> solutionSets = {solutionSetA, solutionSetB, solutionSetC};

    slvr::combineSolutionSets(solutionSets, 1, 2);

    ASSERT_EQ(solutionSets[0][0].numberOfSolutions, 1);
    ASSERT_EQ(solutionSets[0][1].numberOfSolutions, 3);

    ASSERT_EQ(solutionSets[1][0].numberOfSolutions, 4);

    ASSERT_EQ(solutionSets[2][0].numberOfSolutions, 1);
    ASSERT_EQ(solutionSets[2][1].numberOfSolutions, 1);
    ASSERT_EQ(solutionSets[2][2].numberOfSolutions, 2);
}

TEST(CalcProbs, 0)
{
    using namespace mswptileconsts;
    using namespace slvrtileconsts;

    mswp::MineSweeper board(2, 
    {
        V1, V1,
        H1, B0
    });

    slvr::MineSweeperSolver solver(board);

    slvr::TileProbs tileProbs;
    slvr::calculateProbs(solver, tileProbs);

    ASSERT_FLOAT_EQ(tileProbs[2], 0.5);
    ASSERT_FLOAT_EQ(tileProbs[3], 0.5);
}

TEST(CalcProbs, 1)
{
    using namespace mswptileconsts;
    using namespace slvrtileconsts;

    mswp::MineSweeper board(3, 
    {
        V1, V1, V1,
        H1, B0, H1
    });

    slvr::MineSweeperSolver solver(board);

    slvr::TileProbs tileProbs;
    slvr::calculateProbs(solver, tileProbs);

    ASSERT_FLOAT_EQ(tileProbs[3], 0);
    ASSERT_FLOAT_EQ(tileProbs[4], 1);
    ASSERT_FLOAT_EQ(tileProbs[5], 0);
}

TEST(CalcProbs, 2)
{
    using namespace mswptileconsts;
    using namespace slvrtileconsts;

    mswp::MineSweeper board(3, 
    {
        V2, F3, B3,
        V2, F3, F3,
        V1, V2, V2,
    });

    slvr::MineSweeperSolver solver(board);

    slvr::TileProbs tileProbs;
    slvr::calculateProbs(solver, tileProbs);

    ASSERT_FLOAT_EQ(tileProbs[2], 1);
}

TEST(CalcProbs, 3)
{
    using namespace mswptileconsts;
    using namespace slvrtileconsts;

    mswp::MineSweeper board(3, 
    {
        B0, V2, H1,
        H2, V4, B1,
        F0, B1, H2
    });

    slvr::MineSweeperSolver solver(board);

    slvr::TileProbs tileProbs;
    slvr::calculateProbs(solver, tileProbs);

    ASSERT_FLOAT_EQ(tileProbs[0], 0.5);
    ASSERT_FLOAT_EQ(tileProbs[2], 0.5);
    ASSERT_FLOAT_EQ(tileProbs[3], 0.5);
    ASSERT_FLOAT_EQ(tileProbs[5], 0.5);
    ASSERT_FLOAT_EQ(tileProbs[7], 0.5);
    ASSERT_FLOAT_EQ(tileProbs[8], 0.5);
}

TEST(CalcProbs, 4)
{
    using namespace mswptileconsts;
    using namespace slvrtileconsts;

    mswp::MineSweeper board(4, 
    {
        B0, V1, V1, H1,
        H1, V1, V1, B0,
    });

    slvr::MineSweeperSolver solver(board);

    slvr::TileProbs tileProbs;
    slvr::calculateProbs(solver, tileProbs);

    ASSERT_FLOAT_EQ(tileProbs[0], 0.5);
    ASSERT_FLOAT_EQ(tileProbs[3], 0.5);
    ASSERT_FLOAT_EQ(tileProbs[4], 0.5);
    ASSERT_FLOAT_EQ(tileProbs[7], 0.5);
}

TEST(CalcProbs, 5)
{
    using namespace mswptileconsts;
    using namespace slvrtileconsts;

    mswp::MineSweeper board(3, 
    {
        H2, B1, H2,
        V3, F1, V3,
        V3, F1, V3,
        H2, B1, H2,
    });

    slvr::MineSweeperSolver solver(board);

    slvr::TileProbs tileProbs;
    slvr::calculateProbs(solver, tileProbs);

    ASSERT_FLOAT_EQ(tileProbs[0], 0);
    ASSERT_FLOAT_EQ(tileProbs[1], 1);
    ASSERT_FLOAT_EQ(tileProbs[2], 0);

    ASSERT_FLOAT_EQ(tileProbs[9],  0);
    ASSERT_FLOAT_EQ(tileProbs[10], 1);
    ASSERT_FLOAT_EQ(tileProbs[11], 0);
}

TEST(CalcProbs, 6)
{
    using namespace mswptileconsts;
    using namespace slvrtileconsts;

    mswp::MineSweeper board(3, 
    {
        H2, B1, H2,
        V3, F1, V3,
        V3, F1, V3,
        B1, H2, B1,
    });

    slvr::MineSweeperSolver solver(board);

    slvr::TileProbs tileProbs;
    slvr::calculateProbs(solver, tileProbs);

    ASSERT_FLOAT_EQ(tileProbs[0], 0.5);
    ASSERT_FLOAT_EQ(tileProbs[1], 0.5);
    ASSERT_FLOAT_EQ(tileProbs[2], 0.5);

    ASSERT_FLOAT_EQ(tileProbs[9],  0.5);
    ASSERT_FLOAT_EQ(tileProbs[10], 0.5);
    ASSERT_FLOAT_EQ(tileProbs[11], 0.5);
}

TEST(CalcProbs, 7)
{
    using namespace mswptileconsts;
    using namespace slvrtileconsts;

    mswp::MineSweeper board(3, 
    {
        H2, B1, H2,
        V3, F1, V3,
        V3, F1, V3,
        B1, H2, B1,
        H1, H2, H1
    });

    slvr::MineSweeperSolver solver(board);

    slvr::TileProbs tileProbs;
    slvr::calculateProbs(solver, tileProbs);

    ASSERT_FLOAT_EQ(tileProbs[0], 1.0/3);
    ASSERT_FLOAT_EQ(tileProbs[1], 2.0/3);
    ASSERT_FLOAT_EQ(tileProbs[2], 1.0/3);

    ASSERT_FLOAT_EQ(tileProbs[9],  1.0/3);
    ASSERT_FLOAT_EQ(tileProbs[10], 2.0/3);
    ASSERT_FLOAT_EQ(tileProbs[11], 1.0/3);
}