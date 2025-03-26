#include "mine_sweeper_solver.hpp"
#include "util.hpp"
#include "log.hpp"
#include <cstring>

namespace slvr
{

MineSweeperSolver::MineSweeperSolver(mswp::BoardWidth width, mswp::BoardHeight height, mswp::BombCount bombCount, const mswp::TileString& initString) :
    m_Width{width},
    m_Size{util::multI8sToI16(width, height)},
    m_TileString{initString},
    m_RemainingBombs{bombCount},
    m_RemainingTiles{m_Size-m_RemainingBombs}
{

}

inline void updateTile(const mswp::TileStringIndex i, const mswp::TileStringWidth width, const mswp::TileStringSize size, Tiles& outTiles, 
                       mswp::BoardSize& outModifiedSize, bool* outIsModified, ModifiedBuffer& outModified)
{
    Tile& centerTile = outTiles[i];
    bool centerTileHidden = centerTile.hidden();
    bool centerTileBomb = centerTile.bombProb == 1.0;

    int8_t centerHiddenTiles = 0;

    util::applyFuncToAdjObjects<Tiles, Tile>(i, width, size, outTiles, 
    [&](int32_t j, Tile& adjTile) 
    {
        bool adjTileHidden = adjTile.hidden();
        bool adjTileBomb = adjTile.bombProb == 1.0;

        adjTile.adjUnknowns -= !centerTileHidden && !adjTileHidden && !adjTileBomb;
        adjTile.adjBombs -= centerTileBomb && !adjTileHidden && !adjTileBomb;

        centerHiddenTiles += adjTileHidden;
        centerTile.adjBombs -= adjTileBomb && !adjTileHidden && !centerTileBomb;

        if (!adjTileHidden && !adjTileBomb && !outIsModified[j])
        {
            outModified[outModifiedSize] = j;
            outIsModified[j] = true;
            outModifiedSize++;
        }
    });

    bool visibleTile = !centerTileHidden && !centerTileBomb;
    centerTile.adjUnknowns = (centerHiddenTiles*visibleTile) + (-1*!visibleTile);

    if (!centerTileHidden && !centerTileBomb && !outIsModified[i])
    {
        outModified[outModifiedSize] = i;
        outIsModified[i] = true;
        outModifiedSize++;
    }
}

void MineSweeperSolver::update(const mswp::TileString& otherTileString)
{
    mswp::TileStringWidth width = otherTileString.width();
    mswp::TileStringSize size = otherTileString.size();

    bool isTileModified[MSWP_MAX_TILES];
    memset(isTileModified, false, MSWP_MAX_TILES);
    m_ModifiedBufferSize = 0;

    for (mswp::TileStringIndex i = 0; i < size; i++)
    {
        if (m_TileString[i] != otherTileString[i])
        {
            m_TileString[i] = otherTileString[i];
            switch (m_TileString[i])
            {
            case mswp::TileChar::VISIBLE_0:
                m_Tiles[i].adjBombs = 0;
                m_Tiles[i].bombProb = 0;
                break;
            case mswp::TileChar::VISIBLE_1:
                m_Tiles[i].adjBombs = 1;
                m_Tiles[i].bombProb = 0;
                break;
            case mswp::TileChar::VISIBLE_2:
                m_Tiles[i].adjBombs = 2;
                m_Tiles[i].bombProb = 0;
                break;
            case mswp::TileChar::VISIBLE_3:
                m_Tiles[i].adjBombs = 3;
                m_Tiles[i].bombProb = 0;
                break;
            case mswp::TileChar::VISIBLE_4:
                m_Tiles[i].adjBombs = 4;
                m_Tiles[i].bombProb = 0;
                break;
            case mswp::TileChar::VISIBLE_5:
                m_Tiles[i].adjBombs = 5;
                m_Tiles[i].bombProb = 0;
                break;
            case mswp::TileChar::VISIBLE_6:
                m_Tiles[i].adjBombs = 6;
                m_Tiles[i].bombProb = 0;
                break;
            case mswp::TileChar::VISIBLE_7:
                m_Tiles[i].adjBombs = 7;
                m_Tiles[i].bombProb = 0;
                break;
            case mswp::TileChar::VISIBLE_8:
                m_Tiles[i].adjBombs = 8;
                m_Tiles[i].bombProb = 0;
                break;
            case mswp::TileChar::VISIBLE_BOMB:
                m_Tiles[i].bombProb = 1;
                break;
            case mswp::TileChar::HIDDEN:
                m_Tiles[i].bombProb = NAN;
                m_Tiles[i].adjBombs = -1;
                m_Tiles[i].adjUnknowns = -1;
                break;
            case mswp::TileChar::FLAGGED:
                m_Tiles[i].bombProb = 1;
                break;
            
            default:
                break;
            }
            updateTile(i, width, size, m_Tiles, m_ModifiedBufferSize, isTileModified, m_ModifiedBuffer);
        }
    }
}
void MineSweeperSolver::applyFuncToAll(std::function<void(const mswp::BoardIndex i, Tile& outTile)> func)
{
    for (mswp::BoardIndex i = 0; i < m_Size; i++)
    {
        func(i, m_Tiles[i]);
    }
}
void MineSweeperSolver::applyFuncToAll(std::function<void(Tile& outTile)> func)
{
    for (mswp::BoardIndex i = 0; i < m_Size; i++)
    {
        func(m_Tiles[i]);
    }
}
void MineSweeperSolver::applyFuncToAll(std::function<void(const mswp::BoardIndex i)> func)
{
    for (mswp::BoardIndex i = 0; i < m_Size; i++)
    {
        func(i);
    }
}

void MineSweeperSolver::applyFuncToModified(std::function<void(const mswp::BoardIndex i, Tile& outTile)> func)
{
    for (mswp::BoardIndex i = 0; i < m_ModifiedBufferSize; i++)
    {
        func(m_ModifiedBuffer[i], m_Tiles[m_ModifiedBuffer[i]]);
    }
}
void MineSweeperSolver::applyFuncToModified(std::function<void(Tile& outTile)> func)
{
    for (mswp::BoardIndex i = 0; i < m_ModifiedBufferSize; i++)
    {
        func(m_Tiles[m_ModifiedBuffer[i]]);
    }
}
void MineSweeperSolver::applyFuncToModified(std::function<void(const mswp::BoardIndex i)> func)
{
    for (mswp::BoardIndex i = 0; i < m_ModifiedBufferSize; i++)
    {
        func(m_ModifiedBuffer[i]);
    }
}

Tile& MineSweeperSolver::operator[](mswp::BoardIndex i)
{
    return m_Tiles[i];
}
const Tile& MineSweeperSolver::operator[](mswp::BoardIndex i) const
{
    return m_Tiles[i];
}

mswp::BoardWidth MineSweeperSolver::width() const
{
    return m_Width;
}
mswp::BoardSize MineSweeperSolver::size() const
{
    return m_Size;
}

const mswp::TileString& MineSweeperSolver::tileString() const
{
    return m_TileString;
}
mswp::BombCount MineSweeperSolver::remainingBombs() const
{
    return m_RemainingBombs;
}
mswp::BoardSize MineSweeperSolver::remainingTiles() const
{
    return m_RemainingTiles;
}

const Tiles& MineSweeperSolver::tiles() const
{
    return m_Tiles;
}

const ModifiedBuffer& MineSweeperSolver::modifiedBuffer() const
{
    return m_ModifiedBuffer;
}
mswp::BoardSize MineSweeperSolver::modifiedBufferSize() const
{
    return m_ModifiedBufferSize;
}

mswp::TileString& MineSweeperSolver::tileString()
{
    return m_TileString;
}
mswp::BombCount& MineSweeperSolver::remainingBombs()
{
    return m_RemainingBombs;
}
mswp::BoardSize& MineSweeperSolver::remainingTiles()
{
    return m_RemainingTiles;
}

Tiles& MineSweeperSolver::tiles()
{
    return m_Tiles;
}

ModifiedBuffer& MineSweeperSolver::modifiedBuffer()
{
    return m_ModifiedBuffer;
}
mswp::BoardSize& MineSweeperSolver::modifiedBufferSize()
{
    return m_ModifiedBufferSize;
}

bool MineSweeperSolver::operator==(const MineSweeperSolver& other) const
{
    if (m_Size != other.m_Size || m_Width != other.m_Width)
    {
        return false;
    }
    for (mswp::BoardIndex i = 0; i < other.size(); i++)
    {
        if ((*this)[i] != other[i])
        {
            return false;
        }
    }
    return true;
}
bool MineSweeperSolver::operator==(const SolverInitList& other) const
{
    if (m_Size != other.size())
    {
        return false;
    }
    for (mswp::BoardIndex i = 0; i < other.size(); i++)
    {
        if ((*this)[i] != *(other.begin() + i) && (*this)[i].hidden() != (other.begin() + i)->hidden())
        {
            return false;
        }
    }
    return true;
}

std::ostream& operator<<(std::ostream &out, const Tile& tile)
{
    if (!tile.hidden())
    {
        if (tile.bombProb == 1)
        {
            out << "XXXX";
        }
        else
        {
            out << 'B' << std::to_string(static_cast<int>(tile.adjBombs))[0] << 'H' << std::to_string(static_cast<int>(tile.adjUnknowns))[0];
        }
    }
    else
    {
        out << "####";
    }
    return out;
}

std::ostream& operator<<(std::ostream &out, const MineSweeperSolver& mineSweeperSolver)
{
    out << "Board:\n";
    mswp::BoardWidth yMax = mineSweeperSolver.size() / mineSweeperSolver.width();
    for (mswp::BoardIndex i = 0; i < mineSweeperSolver.size(); i++)
    {
        out << mineSweeperSolver[i] << ' ';
        if (i % mineSweeperSolver.width() == mineSweeperSolver.width() - 1)
        {
            out << '\n';
            mswp::BoardWidth y = (i / mineSweeperSolver.width()) + 1;
            if (y == yMax)
            {
                continue;
            }
        }
    }
    return out;
}

} // namespace slvr end