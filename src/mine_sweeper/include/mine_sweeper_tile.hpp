#pragma once

#include <cstdint>

namespace mswp
{

#pragma pack(push, 1)

#define MSWP_COMPACT_TILES 1

struct Tile
{
    /**
     * @brief Tile state, tracks whether tile is visible, has bomb, and or is flagged.
     * 
     */
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
    /**
     * @brief Detects if other tile state and adjBomb count are equal to ours.
     * 
     * @param other 
     * @return true 
     * @return false 
     */
    bool operator==(const Tile other) const
    {
        return state == other.state && adjBombs == other.adjBombs;
    }
#ifdef MSWP_COMPACT_TILES
    uint8_t adjBombs : 4;
    State state : 4;
#else
    uint8_t adjBombs;
    State state;
#endif
};

#pragma pack(pop)

/**
 * @brief Bit ORs two tile states.
 * 
 * @param a state a
 * @param b state b
 * @return constexpr Tile::State 
 */
constexpr Tile::State operator|(Tile::State a, Tile::State b)
{
    return static_cast<Tile::State>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

/**
 * @brief Bit XORs two tile states.
 * 
 * @param a state a
 * @param b state b
 * @return constexpr Tile::State 
 */
constexpr Tile::State operator^(Tile::State a, Tile::State b)
{
    return static_cast<Tile::State>(static_cast<uint8_t>(a) ^ static_cast<uint8_t>(b));
}

/**
 * @brief Bit ANDs two tile states.
 * 
 * @param a state a
 * @param b state b
 * @return constexpr Tile::State 
 */
constexpr Tile::State operator&(Tile::State a, Tile::State b)
{
    return static_cast<Tile::State>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
}

} // mswp end