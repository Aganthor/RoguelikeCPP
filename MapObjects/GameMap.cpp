#include "GameMap.h"

namespace Map
{
    CGameMap::CGameMap() : m_Width { 0 }, m_Height { 0 }
    {
    }

    CGameMap::CGameMap(int w, int h) : m_Width { w }, m_Height { h }
    {
        InitTiles();
    }

    void CGameMap::InitTiles(void)
    {
        for (auto col = 0; col < MAP_HEIGHT; ++col)
        {
            for (auto row = 0; row < MAP_WIDTH; ++row)
            {
                m_GameMap[col][row].setBlocked(false);
            }
        }

        m_GameMap[30][22].setBoth(true, true);
        m_GameMap[31][22].setBoth(true, true);
        m_GameMap[32][22].setBoth(true, true);
    }
}//namespace