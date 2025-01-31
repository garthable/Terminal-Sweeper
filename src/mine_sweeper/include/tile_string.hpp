#pragma once

#include <cstdint>
#include <array>
#include <iostream>

#include "mine_sweeper_constants.hpp"
#include "mine_sweeper_tile.hpp"

namespace mswp
{

#pragma pack(push, 1)

struct TileChar
{
    enum TileCharEnum : uint8_t 
    {
        VISIBLE_0 = 0u,
        VISIBLE_1 = 1u,
        VISIBLE_2 = 2u,
        VISIBLE_3 = 3u,
        VISIBLE_4 = 4u,
        VISIBLE_5 = 5u,
        VISIBLE_6 = 6u,
        VISIBLE_7 = 7u,
        VISIBLE_8 = 8u,
        VISIBLE_BOMB = 9u,
        HIDDEN = 10u,
        FLAGGED = 11u,
    };
    TileCharEnum state0 : 4;
    TileCharEnum state1 : 4;
};

#pragma pack(pop)

typedef uint16_t TileStringSize;
typedef TileStringSize TileStringIndex;
typedef std::array<TileChar, MSWP_MAX_TILES/2> TileChars;
typedef std::initializer_list<Tile> TileStringInitList;

class TileString
{
public:
    TileString();
    TileString(TileStringSize size);
    TileString(TileStringInitList&& tiles);
    TileString(const TileStringInitList& tiles);
    void set(TileStringIndex i, TileChar::TileCharEnum tileCharEnum);
    TileChar::TileCharEnum operator[](TileStringIndex i) const;

    bool operator==(TileStringInitList&& tiles) const;
    bool operator==(const TileString& tileChars) const;

    void operator=(TileStringInitList&& tiles);
    void fill(TileChar::TileCharEnum tileCharEnum);

    TileStringSize size() const;
    const TileChars& tileChars() const;

    void reset();
private:
    TileChars m_TileChars;
    const TileStringSize m_Size;
};

std::ostream& operator<<(std::ostream &out, const TileString& tileString);

} // mswp end