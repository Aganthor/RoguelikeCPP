#pragma once

#include <memory>
#include <vector>
#include <cstddef>
#include <map>
#include <cassert>

#include <libtcod.hpp>

#include "Tile.h"
#include "Rect.h"

namespace Map
{
    const std::size_t MAP_WIDTH = 80;
    const std::size_t MAP_HEIGHT = 45;
    const std::size_t MAX_ROOMS = 30;

    class CGameMap
    {
    public:
        CGameMap();
        ~CGameMap();

        void MakeMap(void);
        void RecomputeFovMap(int x, int y, bool light_walls = true, TCOD_fov_algorithm_t algorithm = FOV_BASIC);
        
        //Getters and setters
        const int getWidth() const { return m_Width; }
        const int getHeight() const { return m_Height; }
        void setWidth(int w) { m_Width = w; ResizeGameMap(); }
        void setHeight(int h) { m_Height = h; ResizeGameMap(); }
        void setWidthHeight(int w, int h) { m_Width = w; m_Height = h; ResizeGameMap(); }
        const TCODColor getColorCode(const std::string& color_id) const;
        CTile& getTile(int x, int y) { return m_GameMap[x][y]; }
        bool isBlocked(int x, int y);
        void setRecomputeFov(bool recompute) {m_RecomputeFov = recompute; }
        bool RecomputeFov() { return m_RecomputeFov; }

        const CRect& getFirstRoom(void)
        {
            assert(m_Rooms.size() > 1);
            return *m_Rooms[0];
        }

        const TCODMap* getFovMap(void) const { return m_FovMap.get(); }

    private:
        void InitTiles(void);
        void InitFovMap(void);
        void ResizeGameMap(void);
        void CreateRoom(CRect& room);
        void CreateHorizontalTunnel(int x1, int x2, int y);
        void CreateVerticalTunnel(int y1, int y2, int x);

    private:
        int m_Width;
        int m_Height;

        int m_RoomMaxSize;
        int m_RoomMinSize;

        const std::size_t FOV_RADIUS = 10;
        const bool FOV_LIGHT_WALLS = true;

        std::unique_ptr<TCODMap> m_FovMap;
        bool m_RecomputeFov;

        std::map<std::string, TCODColor> m_ColorDict;
        std::vector<std::vector<CTile>> m_GameMap;
        std::vector<std::unique_ptr<CRect>> m_Rooms;
    };
}