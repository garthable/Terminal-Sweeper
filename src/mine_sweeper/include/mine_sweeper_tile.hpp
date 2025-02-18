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
    Tile() 
    {}
    constexpr Tile(uint8_t&& adjBombs, State&& state) :
        adjBombs{adjBombs},
        state{state}
    {}
    bool operator==(const Tile other) const
    {
        return state == other.state && adjBombs == other.adjBombs;
    }
    uint8_t adjBombs : 4;
    State state : 4;
};

#pragma pack(pop)

constexpr Tile::State operator|(Tile::State a, Tile::State b)
{
    return static_cast<Tile::State>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

constexpr Tile::State operator^(Tile::State a, Tile::State b)
{
    return static_cast<Tile::State>(static_cast<uint8_t>(a) ^ static_cast<uint8_t>(b));
}

constexpr Tile::State operator&(Tile::State a, Tile::State b)
{
    return static_cast<Tile::State>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
}

} // mswp end