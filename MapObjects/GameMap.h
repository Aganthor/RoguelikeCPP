#pragma once

#include <array>
#include <cstddef>

#include "Tile.h"

namespace Map
{

const std::size_t MAP_WIDTH = 80;
const std::size_t MAP_HEIGHT = 45;

class CGameMap
{
public:
 
public:
    CGameMap();
    CGameMap(int w, int h);
    ~CGameMap();

    //Getters and setters
    int getWidth() { return m_Width; }
    int getHeight() { return m_Height; }
    void setWidth(int w) { m_Width = w; }
    void setHeight(int h) { m_Height = h; }
    void setWidthHeight(int w, int h) { m_Width = w; m_Height = h;}

private:
    void InitTiles(void);

private:
    int m_Width;
    int m_Height;

    template <class T, size_t ROW, size_t COL>
    using Matrix = std::array<std::array<T, COL>, ROW>;
    Matrix<CTile, MAP_WIDTH, MAP_HEIGHT> m_GameMap;
};
}