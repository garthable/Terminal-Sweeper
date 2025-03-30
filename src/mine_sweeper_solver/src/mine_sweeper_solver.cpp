#include "mine_sweeper_solver.hpp"
#include "util.hpp"
#include "log.hpp"
#include <cstring>

namespace slvr
{

MineSweeperSolver::MineSweeperSolver(const mswp::MineSweeper& mineSweeper) :
    m_Width{mineSweeper.width()},
    m_Size{mineSweeper.size()},
    m_TileString{mineSweeper.tileString()},
    m_RemainingBombs{mineSweeper.flagsRemaining()},
    m_RemainingDeepTiles{m_Size}
{
    mswp::TileStringSize size = m_TileString.size();

    m_TilesWithAdjBombBufferSize = 0;

    for (mswp::TileStringIndex i = 0; i < size; i++)
    {
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
        updateTile(i);
    }
}

void MineSweeperSolver::updateTile(const mswp::TileStringIndex i, bool unflag)
{
    Tile& centerTile = m_Tiles[i];
    bool centerTileHidden = centerTile.hidden();
    bool centerTileBomb = centerTile.bombProb == 1.0;

    int8_t centerHiddenTiles = 0;

    if (!m_IsNotDeepTile[i] && !centerTile.hidden())
    {
        m_RemainingDeepTiles--;
        m_IsNotDeepTile[i] = true;
    }

    util::applyFuncToAdjObjects<Tiles, Tile>(i, m_Width, m_Size, m_Tiles, 
    [&](int32_t j, Tile& adjTile) 
    {
        bool adjTileHidden = adjTile.hidden();
        bool adjTileBomb = adjTile.bombProb == 1.0;

        adjTile.adjUnknowns -= !centerTileHidden && !adjTileHidden && !adjTileBomb && !unflag;
        adjTile.adjBombs -= centerTileBomb && !adjTileHidden && !adjTileBomb && !unflag;
        adjTile.adjUnknowns += centerTileHidden && !adjTileHidden && !adjTileBomb && unflag;
        adjTile.adjBombs += !centerTileBomb && !adjTileHidden && !adjTileBomb && unflag;

        centerHiddenTiles += adjTileHidden;
        centerTile.adjBombs -= adjTileBomb && !adjTileHidden && !centerTileBomb;

        if (!m_IsNotDeepTile[j] && !centerTile.hidden() && centerTile.bombProb != 1 && adjTile.hidden())
        {
            m_IsNotDeepTile[j] = true;
            m_RemainingDeepTiles--;
        }
    });

    bool visibleTile = !centerTileHidden && !centerTileBomb;
    centerTile.adjUnknowns = (centerHiddenTiles*visibleTile) + (-1*!visibleTile);
}

void MineSweeperSolver::update(const mswp::TileString& otherTileString)
{
    mswp::TileStringSize size = otherTileString.size();

    m_TilesWithAdjBombBufferSize = 0;

    for (mswp::TileStringIndex i = 0; i < size; i++)
    {
        if (m_TileString[i] != otherTileString[i])
        {
            bool unflag = false;
            // Flagged -> Not Flagged
            if (m_TileString[i] == mswp::TileChar::FLAGGED && otherTileString[i] != mswp::TileChar::FLAGGED)
            {
                unflag = true;
                m_RemainingBombs++;
            }
            // Not Flagged -> Flagged
            if (m_TileString[i] != mswp::TileChar::FLAGGED && otherTileString[i] == mswp::TileChar::FLAGGED)
            {
                m_RemainingBombs--;
            }
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
            updateTile(i, unflag);
        }
    }

    for (mswp::TileStringIndex i = 0; i < size; i++)
    {
        if ((m_Tiles[i].adjBombs != 0 || m_Tiles[i].adjUnknowns != 0) && !m_Tiles[i].hidden() && m_Tiles[i].bombProb != 1)
        {
            m_TilesWithAdjBombBuffer[m_TilesWithAdjBombBufferSize] = i;
            m_TilesWithAdjBombBufferSize++;
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

void MineSweeperSolver::applyFuncToTilesWithAdjBombs(std::function<void(const TilesWithAdjBombSize i, Tile& outTile)> func)
{
    for (TilesWithAdjBombSize i = 0; i < m_TilesWithAdjBombBufferSize; i++)
    {
        func(m_TilesWithAdjBombBuffer[i], m_Tiles[m_TilesWithAdjBombBuffer[i]]);
    }
}
void MineSweeperSolver::applyFuncToTilesWithAdjBombs(std::function<void(Tile& outTile)> func)
{
    for (TilesWithAdjBombSize i = 0; i < m_TilesWithAdjBombBufferSize; i++)
    {
        func(m_Tiles[m_TilesWithAdjBombBuffer[i]]);
    }
}
void MineSweeperSolver::applyFuncToTilesWithAdjBombs(std::function<void(const TilesWithAdjBombSize i)> func)
{
    for (TilesWithAdjBombSize i = 0; i < m_TilesWithAdjBombBufferSize; i++)
    {
        func(m_TilesWithAdjBombBuffer[i]);
    }
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
    if (static_cast<size_t>(m_Size) != other.size())
    {
        return false;
    }
    for (size_t i = 0; i < other.size(); i++)
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