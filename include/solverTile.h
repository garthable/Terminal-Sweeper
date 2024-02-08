#ifndef SOLVERTILE
#define SOLVERTILE

#include <vector>
#include <array>

struct solverTile
{
    std::vector<solverTile*> adjSolverTiles;
    std::array<float, 9u> probabilityOfHavingNAdjBombs;
    std::vector<bool> bombBackTracking;
    float bombProbability;
    uint16_t x;
    uint16_t y;
    uint16_t adjBombsAmount;
    uint8_t solverTileState;

    bool visited;

    solverTile(const uint16_t& _x, const uint16_t& _y)
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