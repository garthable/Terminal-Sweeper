#include "mine_sweeper_solver.hpp"
#include "util.hpp"

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

inline void updateTile(Tile& outTile, Tiles& outTiles)
{
    
}

void MineSweeperSolver::update(const mswp::TileString& otherTileString)
{
    mswp::TileStringSize size = otherTileString.size();
    for (mswp::TileStringIndex i = 0; i < size; i++)
    {
        if (m_TileString[i] != otherTileString[i])
        {
            m_TileString[i] = otherTileString[i];
            switch (m_TileString[i])
            {
            case mswp::TileChar::VISIBLE_0:
                m_Tiles[i].adjBombs = 0;
                m_Tiles[i].adjUnkowns = 0;
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
                break;
            case mswp::TileChar::FLAGGED:
                m_Tiles[i].bombProb = 1;
                break;
            
            default:
                break;
            }
        }
    }
}
void MineSweeperSolver::applyFuncToAll(std::function<void(Tile& tile)> func)
{

}
Tile& MineSweeperSolver::operator[](mswp::BoardIndex i)
{

}
const Tile& MineSweeperSolver::operator[](mswp::BoardIndex i) const
{

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

} // namespace slvr end