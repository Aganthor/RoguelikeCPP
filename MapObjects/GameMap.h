#pragma once

#include <memory>
#include <random>
#include <vector>
#include <cstddef>
#include <map>

#include <libtcod.hpp>

#include "Tile.h"
#include "Rect.h"

class RandomInt
{
public:
    std::random_device m_Rd;
    std::mt19937 m_Mt;
    std::uniform_int_distribution<int> m_Dist;

    RandomInt() : m_Rd{}, m_Mt{m_Rd()} {}

    int MakeRnd(int min, int max)
    {
        //m_Dist
        return 0;
    }

};

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

        //Getters and setters
        const int getWidth() const { return m_Width; }
        const int getHeight() const { return m_Height; }
        void setWidth(int w) { m_Width = w; ResizeGameMap(); }
        void setHeight(int h) { m_Height = h; ResizeGameMap(); }
        void setWidthHeight(int w, int h) { m_Width = w; m_Height = h; ResizeGameMap(); }
        const TCODColor getColorCode(const std::string& color_id) const;
        const CTile& getTile(int x, int y) const { return m_GameMap[x][y]; }
        bool isBlocked(int x, int y);

    private:
        void InitTiles(void);
        void ResizeGameMap(void);
        void CreateRoom(const CRect& room);
        void CreateHorizontalTunnel(int x1, int x2, int y);
        void CreateVerticalTunnel(int y1, int y2, int x);

    private:
        int m_Width;
        int m_Height;

        int m_RoomMaxSize;
        int m_RoomMinSize;

        std::map<std::string, TCODColor> m_ColorDict;
        std::vector<std::vector<CTile>> m_GameMap;
        std::vector<std::unique_ptr<CRect>> m_Rooms;
    };
}