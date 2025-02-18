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
typedef uint8_t TileStringWidth;
typedef TileStringSize TileStringIndex;
typedef std::array<TileChar, MSWP_MAX_TILES/2> TileChars;
typedef std::initializer_list<Tile> TileStringInitList;

inline TileChar::TileCharEnum tileToTileChar(Tile tile)
{
    if (tile.state & Tile::VISIBLE)
    {
        if (tile.state & Tile::BOMB)
        {
            return TileChar::VISIBLE_BOMB;
        }
        return static_cast<TileChar::TileCharEnum>(tile.adjBombs);
    }
    if (tile.state & Tile::FLAGGED)
    {
        return TileChar::FLAGGED;
    }
    return TileChar::HIDDEN;
}

inline char tileCharToChar(TileChar::TileCharEnum tileChar)
{
    switch (tileChar)
    {
    case TileChar::VISIBLE_0:
        return ' ';
    case TileChar::VISIBLE_1:
        return '1';
    case TileChar::VISIBLE_2:
        return '2';
    case TileChar::VISIBLE_3:
        return '3';
    case TileChar::VISIBLE_4:
        return '4';
    case TileChar::VISIBLE_5:
        return '5';
    case TileChar::VISIBLE_6:
        return '6';
    case TileChar::VISIBLE_7:
        return '7';
    case TileChar::VISIBLE_8:
        return '8';

    case TileChar::FLAGGED:
        return '@';
    case TileChar::VISIBLE_BOMB:
        return 'X';

    case TileChar::HIDDEN:
        return '#';
    }
    throw std::runtime_error("INVALID CHARACTER");
}

class TileString
{
public:
    TileString();
    TileString(TileStringSize size, TileStringWidth width);
    TileString(TileStringWidth width, TileStringInitList&& tiles);
    TileString(TileStringWidth width, const TileStringInitList& tiles);
    void set(TileStringIndex i, TileChar::TileCharEnum tileCharEnum);
    TileChar::TileCharEnum operator[](TileStringIndex i) const;

    bool operator==(TileStringInitList&& tiles) const;
    bool operator==(const TileString& tileChars) const;

    void operator=(TileStringInitList&& tiles);
    void fill(TileChar::TileCharEnum tileCharEnum);

    TileStringSize size() const;
    TileStringWidth width() const;
    const TileChars& tileChars() const;

    void reset();
private:
    TileChars m_TileChars;
    const TileStringSize m_Size;
    const TileStringWidth m_Width;
};

std::ostream& operator<<(std::ostream &out, const TileString& tileString);

} // mswp end