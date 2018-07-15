#include "GameMap.h"

#include <algorithm>

#include "../Utility/Random.h"

namespace Map
{
    CGameMap::CGameMap() : m_Width { MAP_WIDTH }, m_Height { MAP_HEIGHT },
                           m_RoomMaxSize {10}, m_RoomMinSize {6}
    {
        ResizeGameMap();
        InitTiles();

        //Prepare the colors for our different tiles.
        m_ColorDict.insert(std::make_pair<std::string, TCODColor>("dark_wall", TCODColor(0, 0, 100)));
        m_ColorDict.insert(std::make_pair<std::string, TCODColor>("dark_ground", TCODColor(50, 50, 150)));

        //Random number generator
        Random::init();
    }

    CGameMap::~CGameMap()
    {

    }

    ///////////////////////////////////////////////////////////////////////////
    // As the name implies, initialize all the tiles in the map.
    ///////////////////////////////////////////////////////////////////////////
    void CGameMap::InitTiles(void)
    {
        for (auto y = 0; y < MAP_HEIGHT; ++y)
        {
            for (auto x = 0; x < MAP_WIDTH; ++x)
            {
                m_GameMap[x][y].setBlocked(true);
            }
        }   
    }

    ///////////////////////////////////////////////////////////////////////////
    // Resize the game map vector according to the width and height member
    // variables.
    ///////////////////////////////////////////////////////////////////////////
    void CGameMap::ResizeGameMap(void)
    {
        m_GameMap.resize(m_Width);
        for (auto &col : m_GameMap)
            col.resize(m_Height);
    }

    ///////////////////////////////////////////////////////////////////////////
    // Function to actually create a map full of rooms and corridors.
    ///////////////////////////////////////////////////////////////////////////
    void CGameMap::MakeMap(void)
    {
        int num_rooms = {0};

        for (auto r = 0; r < MAX_ROOMS; ++r)
        {
            //Generate random room size.
            auto w = Random::intInRange(m_RoomMinSize, m_RoomMaxSize);
            auto h = Random::intInRange(m_RoomMinSize, m_RoomMaxSize);

            //Generate random position without going outside the map.
            auto x = Random::intInRange(0, MAP_WIDTH - w - 1);
            auto y = Random::intInRange(0, MAP_HEIGHT - h - 1);

            auto new_room = std::make_unique<CRect>(x, y, w, h);

            //Run through the other rooms and see if they intersect with this one.
            for (auto room : m_Rooms)
            {
                if (new_room->Intersect((*room))
                    break;
            }

        }
        /*
        CreateRoom(CRect(20, 15, 10, 15));
        CreateRoom(CRect(35, 15, 10, 15));
        CreateHorizontalTunnel(25, 40, 23);
        */
    }

    ///////////////////////////////////////////////////////////////////////////
    // Function that will create a room in the map, From (x1,y1) to (x2,y2)
    // we'll set the tiles to be walkable so that the player can walk in it.
    ///////////////////////////////////////////////////////////////////////////
    void CGameMap::CreateRoom(const CRect& room)
    {
        for (auto x = room.getX1() + 1; x < room.getX2(); ++x)
            for (auto y = room.getY1() + 1; y < room.getY2(); ++y)            
                m_GameMap[x][y].setFloor();
    }

    ///////////////////////////////////////////////////////////////////////////
    // Creates an horizontal tunnel between two rooms.
    ///////////////////////////////////////////////////////////////////////////
    void CGameMap::CreateHorizontalTunnel(int x1, int x2, int y)
    {
        for (auto x = std::min(x1,x2); x < std::max(x1,x2) + 1; ++x)
            m_GameMap[x][y].setFloor();
    }

    ///////////////////////////////////////////////////////////////////////////
    // Creates a vertical tunnel between two rooms.
    ///////////////////////////////////////////////////////////////////////////
    void CGameMap::CreateVerticalTunnel(int y1, int y2, int x)
    {
        for (auto y = std::min(y1,y2); y < std::max(y1,y2) + 1; ++y)
            m_GameMap[x][y].setFloor();
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
            return TCOD_color_RGB(0, 0, 0);
    }

    ///////////////////////////////////////////////////////////////////////////
    // Checks to see if the player can move therefore he's not blocked by a 
    // wall. Returns true if he can move.
    ///////////////////////////////////////////////////////////////////////////
    bool CGameMap::isBlocked(int x, int y)
    {
        if (m_GameMap[x][y].isBlocked())
            return true;
        else
            return false;
    }
}//namespace