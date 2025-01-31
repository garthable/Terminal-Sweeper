#pragma once

#include <cstdint>

namespace mswp
{

#pragma pack(push, 1)

struct Tile
{
    enum State : uint8_t 
    {
        HIDDEN = 0u,
        BOMB = 1u,
        FLAGGED = 2u,
        VISIBLE = 4u,
    };
    uint8_t adjBombs : 4;
    State state : 4;
};

#pragma pack(pop)

} // mswp end