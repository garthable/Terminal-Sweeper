#pragma once

#include <cstdint>

namespace mswp
{

#pragma pack(push, 1)

enum MineSweeperState : uint8_t 
{
    BOMB = 1u,
    FLAGGED = 2u,
    VISIBLE = 4u,
};

enum MineSweeperStateExport : uint8_t 
{
    EMPTY = 0u,

    V0 = 1u,
    V1 = 2u,
    V2 = 3u,
    V3 = 4u,
    V4 = 5u,
    V5 = 6u,
    V6 = 7u,
    V7 = 8u,
    V8 = 9u,
    HN = 10u,
    HF = 11u,

    EOB = 15u
};

struct MineSweeperTile
{
    uint8_t adjBombs : 4;
    MineSweeperState state : 4;

    operator char() const { return (uint8_t)*this; }
};

struct MineSweeperTileExport
{
    MineSweeperStateExport state0 : 4;
    MineSweeperStateExport state1 : 4;

    operator char() const { return (uint8_t)*this; }
};

#pragma pack(pop)

} // mswp end