#ifndef SOLVERTILE
#define SOLVERTILE

#include <vector>
#include "sVector.hpp"
#include <array>
#include <cstdint>
#include "mineSweeper.hpp"

#define MAX_RECCOMENDED (MAX_TILE_COUNT/4)*3
#define MAX_AMOUNT_OF_GROUPS MAX_TILE_COUNT/9
#define MAX_SIZE_OF_GROUP MAX_TILE_COUNT - (MAX_TILE_COUNT/9)

struct SolverTile
{
    svec::SVector<SolverTile*, 8> adjSolverTiles;
    double bombProbability;
    uint16_t x;
    uint16_t y;
    uint16_t adjBombsAmount;
    uint8_t solverTileState;

    bool visited;

    SolverTile()
    {

    }

    SolverTile(SolverTile&& other) :
        adjSolverTiles{std::move(adjSolverTiles)},
        bombProbability{std::move(bombProbability)},
        x{std::move(other.x)},
        y{std::move(other.y)},
        adjBombsAmount{std::move(other.adjBombsAmount)},
        solverTileState{std::move(other.solverTileState)}
    {
        
    }

    SolverTile(const uint16_t& _x, const uint16_t& _y)
    {
        x = _x;
        y = _y;
        adjBombsAmount = 0u;
        visited = false;
        solverTileState = 0u;
        bombProbability = 0.0;
    }

    void operator=(const SolverTile& other)
    {
        adjSolverTiles = adjSolverTiles;
        bombProbability = bombProbability;
        x = other.x;
        y = other.y;
        adjBombsAmount = other.adjBombsAmount;
        solverTileState = other.solverTileState;
    }

    void operator=(SolverTile&& other)
    {
        adjSolverTiles = adjSolverTiles;
        bombProbability = bombProbability;
        x = other.x;
        y = other.y;
        adjBombsAmount = other.adjBombsAmount;
        solverTileState = other.solverTileState;
    }
    
};

typedef svec::SVector<svec::SVector<SolverTile*, MAX_SIZE_OF_GROUP>, MAX_AMOUNT_OF_GROUPS> GroupedSolverTiles;

#endif