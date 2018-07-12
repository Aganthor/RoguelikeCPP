#include "GameMap.h"

namespace Map
{
    CGameMap::CGameMap() : m_Width { MAP_WIDTH }, m_Height { MAP_HEIGHT }
    {
        InitTiles();

        //Prepare the colors
        m_ColorDict.insert(std::make_pair<std::string, TCODColor>("dark_wall", TCODColor(0, 0, 100)));
        m_ColorDict.insert(std::make_pair<std::string, TCODColor>("dark_ground", TCODColor(50, 50, 150)));
    }

    CGameMap::~CGameMap()
    {

    }

    ///////////////////////////////////////////////////////////////////////////
    // As the name implies, initialize all the tiles in the map.
    ///////////////////////////////////////////////////////////////////////////
    void CGameMap::InitTiles(void)
    {
        for (auto col = 0; col < MAP_HEIGHT; ++col)
        {
            for (auto row = 0; row < MAP_WIDTH; ++row)
            {
                m_GameMap[row][col].setBlocked(false);
            }
        }
        
        m_GameMap[22][30].setBoth(true, true);
        m_GameMap[22][31].setBoth(true, true);
        m_GameMap[22][32].setBoth(true, true);    
    }

    ///////////////////////////////////////////////////////////////////////////
    // Checks the color dictionnary to see if a certain color is present.
    ///////////////////////////////////////////////////////////////////////////
    const TCODColor CGameMap::getColorCode(const std::string& color_id) const
    {
        auto color = m_ColorDict.find(color_id);
        if (color != m_ColorDict.end())
            return color->second;
        else
            return TCODColor(0, 0, 0);
    }

    ///////////////////////////////////////////////////////////////////////////
    // Checks to see if the player can move therefor he's not blocked by a 
    // wall. Returns true if he can move.
    ///////////////////////////////////////////////////////////////////////////
    bool CGameMap::isBlocked(int x, int y)
    {
        //if (m_GameMap[x][y].isBlocked())
        if (m_GameMap[y][x].isBlocked())
            return true;
        else
            return false;
    }
}//namespace