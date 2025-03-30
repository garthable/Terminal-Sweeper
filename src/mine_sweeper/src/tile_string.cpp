#include "tile_string.hpp"
#include "util.hpp"

namespace mswp 
{

TileString::TileString() :
    m_Size{0},
    m_Width{1}
{}
TileString::TileString(TileStringSize size, TileStringWidth width) :
    m_Size{size},
    m_Width{width}
{
    fill(TileChar::HIDDEN);
}
TileString::TileString(TileStringWidth width, TileStringInitList&& tiles) :
    m_Size{static_cast<TileStringSize>(tiles.size())},
    m_Width{width}
{
    for (TileStringIndex i = 0; i < m_Size; i++)
    {
        Tile tile = *(tiles.begin() + i);
        TileChar tileChar = tileToTileChar(tile);
        (*this)[i] = tileChar;
    }
}
TileString::TileString(TileStringWidth width, const TileStringInitList& tiles) :
    m_Size{static_cast<TileStringSize>(tiles.size())},
    m_Width{width}
{
    for (TileStringIndex i = 0; i < m_Size; i++)
    {
        Tile tile = *(tiles.begin() + i);
        TileChar tileChar = tileToTileChar(tile);
        (*this)[i] = tileChar;
    }
}
TileChar& TileString::operator[](TileStringIndex i)
{
    return m_TileChars[i];
}
TileChar TileString::operator[](TileStringIndex i) const
{
    return m_TileChars[i];
}

bool TileString::operator==(TileStringInitList&& tiles) const
{
    for (TileStringSize i = 0; i < m_Size; i++)
    {
        TileChar tileChar = tileToTileChar(*(tiles.begin() + 1));
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
        if ((*this)[i] != tileChars[i])
        {
            return false;
        }
    }
    return true;
}

void TileString::operator=(TileStringInitList&& tiles)
{
    TileChar tileChar = tileToTileChar(*(tiles.begin() + 1));
    for (TileStringIndex i = 0; i < m_Size; i++)
    {
        (*this)[i] = tileChar;
    }
}
void TileString::fill(TileChar tileChar)
{
    for (TileStringIndex i = 0; i < m_Size; i++)
    {
        (*this)[i] = tileChar;
    }
}

TileStringSize TileString::size() const
{
    return m_Size;
}
TileStringWidth TileString::width() const
{
    return m_Width;
}
const TileChars& TileString::tileChars() const
{
    return m_TileChars;
}

void TileString::reset()
{
    fill(TileChar::HIDDEN);
}

TileChars::iterator TileString::begin()
{
    return m_TileChars.begin();
}
TileChars::iterator TileString::end()
{
    return m_TileChars.end();
}
TileChars::const_iterator TileString::begin() const
{
    return m_TileChars.begin();
}
TileChars::const_iterator TileString::end() const
{
    return m_TileChars.end();
}

std::ostream& operator<<(std::ostream &out, const TileString& tileString)
{
    out << "Board:\n";
    out << util::uI8ToLetter(0) << " | ";
    TileStringWidth yMax = tileString.size() / tileString.width();
    for (TileStringIndex i = 0; i < tileString.size(); i++)
    {
        out << tileCharToChar(tileString[i]) << ' ';
        if (i % tileString.width() == tileString.width() - 1)
        {
            out << '\n';
            TileStringWidth y = (i / tileString.width()) + 1;
            if (y == yMax)
            {
                continue;
            }
            out << util::uI8ToLetter(y) << " | ";
        }
    }
    out << "   ";
    for (TileStringIndex i = 0; i < tileString.width(); i++)
    {
        out << "--";
    }
    out << "\n    ";
    for (TileStringIndex i = 0; i < tileString.width(); i++)
    {
        out << util::uI8ToLetter(i) << " ";
    }
    out << "\n";
    return out;
}
std::ostream& operator<<(std::ostream &out, const Tile& tile)
{
    out << tileCharToChar(tileToTileChar(tile));
    return out;
}

} // mswp end