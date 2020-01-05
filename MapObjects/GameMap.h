#pragma once

#include <memory>
#include <vector>
#include <cstddef>
#include <map>
#include <cassert>

#include <libtcod/libtcod.hpp>

#include "Tile.h"
#include "Rect.h"

class Engine;

namespace Map
{
    const int MAP_WIDTH = 80;
    const int MAP_HEIGHT = 45;
    const int MAX_ROOMS = 30;

    class CGameMap
    {
    public:
        CGameMap();
        ~CGameMap();

        //void MakeMap(Engine& engine);
        void makeMap();
        void recomputeFovMap(int x, int y, bool light_walls = true, TCOD_fov_algorithm_t algorithm = FOV_BASIC);
        
        //Getters and setters
        int getWidth() const { return m_Width; }
        int getHeight() const { return m_Height; }
        void setWidth(int w) { m_Width = w; resizeGameMap(); }
        void setHeight(int h) { m_Height = h; resizeGameMap(); }
        void setWidthHeight(int w, int h) { m_Width = w; m_Height = h; resizeGameMap(); }
        const TCODColor getColorCode(const std::string& color_id) const;
        CTile& getTile(int x, int y) { return m_GameMap[x][y]; }
        bool isBlocked(int x, int y);
        void setRecomputeFov(bool recompute) {m_RecomputeFov = recompute; }
        bool recomputeFov() { return m_RecomputeFov; }

        const CRect& getFirstRoom(void)
        {
            assert(m_Rooms.size() > 1);
            return *m_Rooms[0];
        }

        const TCODMap* getFovMap(void) const { return m_FovMap.get(); }

    private:
        void initTiles(void);
        void initFovMap(void);
        void resizeGameMap(void);
        void createRoom(CRect& room);
        void createHorizontalTunnel(int x1, int x2, int y);
        void createVerticalTunnel(int y1, int y2, int x);
        void placeEntities(Engine& engine, CRect& room);

    private:
        int m_Width;
        int m_Height;

        int m_RoomMaxSize;
        int m_RoomMinSize;

        const int FOV_RADIUS = 10;
        const bool FOV_LIGHT_WALLS = true;
		const int MAX_ENNEMIES_PER_ROOM = 3;

        std::unique_ptr<TCODMap> m_FovMap;
        bool m_RecomputeFov;

        std::map<std::string, TCODColor> m_ColorDict;
        std::vector<std::vector<CTile>> m_GameMap;
        std::vector<std::unique_ptr<CRect>> m_Rooms;
    };
}
