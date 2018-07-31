
#include "GameMap.h"

#include <algorithm>
#include <iostream>

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
        int num_rooms {0};
        bool intersect {false};

        for (auto r = 0; r < MAX_ROOMS; ++r)
        {
            //Generate random room size.
            auto w = Random::intInRange(m_RoomMinSize, m_RoomMaxSize);
            auto h = Random::intInRange(m_RoomMinSize, m_RoomMaxSize);

            //Generate random position without going outside the map.
            auto x = Random::intInRange(0, MAP_WIDTH - w - 1);
            auto y = Random::intInRange(0, MAP_HEIGHT - h - 1);

            auto new_room = std::make_unique<CRect>(x, y, w, h);

            if (num_rooms == 0)
            {
                //It'S our first room!!!
                //TODO : we add the player here!
                CreateRoom(*new_room);
                ++num_rooms;
                m_Rooms.push_back(std::move(new_room));
            }
            else
            {
                //Run through the other rooms and see if they intersect with this one.
                //If the new room intersect, toss it out.
                for (auto &room : m_Rooms)
                {
                    if (new_room->Intersect(*room))
                    {
                        new_room.release();
                        intersect = true;
                        break;
                    }
                }
                if (!intersect)
                {
                    CreateRoom(*new_room);
                    auto [new_x, new_y] = new_room->getCenter();

                    //Connect it to the previous one.
                    //Get the center of the previous room
                    auto [prev_x, prev_y] = m_Rooms[num_rooms - 1]->getCenter();

                    //Flip a coin: horizontal or vertical tunnel.
                    if (Random::intInRange(0, 1) == 1)
                    {
                        //First move horizontally, then  vertically.
                        CreateHorizontalTunnel(prev_x, new_x, prev_y);
                        CreateVerticalTunnel(prev_y, new_y, new_x);
                    }
                    else
                    {
                        //First move vertically, then horizontally.
                        CreateVerticalTunnel(prev_y, new_y, prev_x);
                        CreateHorizontalTunnel(prev_x, new_x, new_y);
                    }
                    ++num_rooms;
                    m_Rooms.push_back(std::move(new_room));    
                    intersect = false;                    
                }
            }
        }
        std::cout << "Created " << num_rooms << " rooms." << std::endl;
    }

    ///////////////////////////////////////////////////////////////////////////
    // Function that will create a room in the map, From (x1,y1) to (x2,y2)
    // we'll set the tiles to be walkable so that the player can walk in it.
    ///////////////////////////////////////////////////////////////////////////
    void CGameMap::CreateRoom(CRect& room)
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
