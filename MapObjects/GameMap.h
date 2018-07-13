#pragma once

//#include <array>
#include <vector>
#include <cstddef>
#include <map>

#include <libtcod.hpp>

#include "Tile.h"

namespace Map
{
    const std::size_t MAP_WIDTH = 80;
    const std::size_t MAP_HEIGHT = 45;

    class CGameMap
    {
    public:
        CGameMap();
        ~CGameMap();

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

    private:
        int m_Width;
        int m_Height;

        std::map<std::string, TCODColor> m_ColorDict;

        //template <class T, size_t ROW, size_t COL>
        //using Matrix = std::array<std::array<T, COL>, ROW>;
        //Matrix<CTile, MAP_HEIGHT, MAP_WIDTH> m_GameMap;
        //using NativeMatrix = T[ROW][COL];
        //NativeMatrix<CTile, MAP_WIDTH, MAP_HEIGHT> m_GameMap;

        //https://gitlab.com/DontEatSoapDudley/roguelikedev_challenge/blob/week2/map.hh
        //std::vector<std::vector<Tile>> tiles;
        //Change to make it a vector<vector<CTiles>>
        std::vector<std::vector<CTile>> m_GameMap;

    };
}