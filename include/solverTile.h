#ifndef SOLVERTILE
#define SOLVERTILE

#include <vector>
#include <array>

struct SolverTile
{
    std::vector<SolverTile*> adjSolverTiles;
    double bombProbability;
    uint16_t x;
    uint16_t y;
    uint16_t adjBombsAmount;
    uint8_t solverTileState;

    bool visited;

    SolverTile(const uint16_t& _x, const uint16_t& _y)
    {
        x = _x;
        y = _y;
        adjBombsAmount = 0u;
        visited = false;
        solverTileState = 0u;
        bombProbability = 0.0;
    }
};

#endif