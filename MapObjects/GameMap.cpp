
#include "GameMap.h"

#include <algorithm>
#include <iostream>

#include "../Utility/Random.h"
#include "../Engine.h"

namespace Map
{
    CGameMap::CGameMap() : m_Width { MAP_WIDTH }, m_Height { MAP_HEIGHT },
                           m_RoomMaxSize {10}, m_RoomMinSize {6},
                           m_RecomputeFov {true}
    {
        ResizeGameMap();
        InitTiles();

        m_FovMap = std::make_unique<TCODMap>(m_Width, m_Height);

        //Prepare the colors for our different tiles.
        m_ColorDict.insert(std::make_pair<std::string, TCODColor>("dark_wall", TCODColor(0, 0, 100)));
        m_ColorDict.insert(std::make_pair<std::string, TCODColor>("dark_ground", TCODColor(50, 50, 150)));
        m_ColorDict.insert(std::make_pair<std::string, TCODColor>("light_wall", TCODColor(130, 110, 50)));
        m_ColorDict.insert(std::make_pair<std::string, TCODColor>("light_ground", TCODColor(200, 180, 50)));
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
    // Initialize the Fov map!
    ///////////////////////////////////////////////////////////////////////////
    void CGameMap::InitFovMap(void)
    {
        for (auto y = 0; y < m_Height; ++y)
            for (auto x = 0; x < m_Width; ++x)
                m_FovMap->setProperties(x, y, !m_GameMap[x][y].isBlockingSight(), !m_GameMap[x][y].isBlocked());
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

        //Delete the old Fov Map and create a now one.
        if (auto fovMapPtr = m_FovMap.release(); fovMapPtr)
		{
            delete fovMapPtr;
		}
        m_FovMap = std::make_unique<TCODMap>(m_Width, m_Height);
    }

    ///////////////////////////////////////////////////////////////////////////
    // Function to actually create a map full of rooms and corridors.
    ///////////////////////////////////////////////////////////////////////////
    void CGameMap::MakeMap(Engine& engine)
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
						if (auto ptr = new_room.release(); ptr)
						{
							delete ptr;
						}
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
                    if (Random::flipACoin())
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
                    PlaceEntities(engine, *new_room);
                    m_Rooms.push_back(std::move(new_room));
                    intersect = false;
                }
            }
        }
        std::cout << "Created " << num_rooms << " rooms." << std::endl;
        InitFovMap();

    }

    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////
    void CGameMap::RecomputeFovMap(int x, int y, bool light_walls, TCOD_fov_algorithm_t algorithm)
    {
        m_FovMap->computeFov(x, y, FOV_RADIUS, light_walls, algorithm);
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
    // Place a random entity in the newly created room.
    ///////////////////////////////////////////////////////////////////////////
    void CGameMap::PlaceEntities(Engine& engine, CRect& room)
	{
        //Get a random number of enemies to place;
		auto nbEnemies = Random::intInRange(0, MAX_ENNEMIES_PER_ROOM);

		for (auto nb = 0; nb < MAX_ENNEMIES_PER_ROOM; ++nb)
		{
			//Choose a random place in the room.
			auto x = Random::intInRange( room.getX1() + 1, room.getX2() - 1);
			auto y = Random::intInRange( room.getY1() + 1, room.getY2() - 1);

			if (!engine.EntityPresentAt(x, y))
			{
				if (Random::intInRange(0, 100) < 80)
					engine.CreateEntity(x, y, "Ogre", 'o', TCODColor::desaturatedGreen, true);
				else
					engine.CreateEntity(x, y, "Troll", 'T', TCODColor::darkerGreen, true);
			}
		}
	}

    ///////////////////////////////////////////////////////////////////////////
    // Checks the color dictionnary to see if a certain color is present.
    ///////////////////////////////////////////////////////////////////////////
    const TCODColor CGameMap::getColorCode(const std::string& color_id) const
    {
        if (auto color = m_ColorDict.find(color_id); color != m_ColorDict.end())
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
