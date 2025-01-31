#include "tile_string.hpp"

namespace mswp 
{

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

TileString::TileString() :
    m_Size{0}
{}
TileString::TileString(TileStringSize size) :
    m_Size{size}
{
    fill(TileChar::HIDDEN);
}
TileString::TileString(TileStringInitList&& tiles) :
    m_Size{tiles.size()}
{
    for (TileStringIndex i = 0; i < m_Size; i++)
    {
        Tile tile = *(tiles.begin() + i);
        TileChar::TileCharEnum tileChar = tileToTileChar(tile);
        set(i, tileChar);
    }
}
TileString::TileString(const TileStringInitList& tiles) :
    m_Size{tiles.size()}
{
    for (TileStringIndex i = 0; i < m_Size; i++)
    {
        Tile tile = *(tiles.begin() + i);
        TileChar::TileCharEnum tileChar = tileToTileChar(tile);
        set(i, tileChar);
    }
}
void TileString::set(TileStringIndex i, TileChar::TileCharEnum tileCharEnum)
{
    TileStringIndex byteIndex = i / 2;
    switch (i % 2)
    {
    case 0:
        m_TileChars[byteIndex].state0 = tileCharEnum;
        return;
    case 1:
        m_TileChars[byteIndex].state1 = tileCharEnum;
        return;
    }
}
TileChar::TileCharEnum TileString::operator[](TileStringIndex i) const
{
    TileStringIndex byteIndex = i / 2;
    return i % 2 == 0 ?  m_TileChars[byteIndex].state0 : m_TileChars[byteIndex].state1;
}

bool TileString::operator==(TileStringInitList&& tiles) const
{
    for (TileStringSize i = 0; i < m_Size; i++)
    {
        TileChar::TileCharEnum tileChar = tileToTileChar(*(tiles.begin() + 1));
        if ((*this)[i] == tileChar)
        {
            return false;
        }
    }
    return true;
}
bool TileString::operator==(const TileString& tileChars) const
{
    for (TileStringSize i = 0; i < m_Size; i++)
    {
        if ((*this)[i] == tileChars[i])
        {
            return false;
        }
    }
    return true;
}

void TileString::operator=(TileStringInitList&& tiles)
{
    TileChar::TileCharEnum tileChar = tileToTileChar(*(tiles.begin() + 1));
    for (TileStringIndex i = 0; i < m_Size; i++)
    {
        set(i, tileChar);
    }
}
void TileString::fill(TileChar::TileCharEnum tileCharEnum)
{
    for (TileStringIndex i = 0; i < m_Size; i++)
    {
        set(i, tileCharEnum);
    }
}

TileStringSize TileString::size() const
{
    return m_Size;
}
const TileChars& TileString::tileChars() const
{
    return m_TileChars;
}

void TileString::reset()
{
    fill(TileChar::HIDDEN);
}

std::ostream& operator<<(std::ostream &out, const TileString& tileString)
{
    return out;
}

} // mswp end