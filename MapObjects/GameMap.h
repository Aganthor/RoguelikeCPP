#pragma once

#include <array>

#include "Tile.h"

class CGameMap
{
public:
    const int MAP_WIDTH = 80;
    const int MAP_HEIGHT = 45;
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
    std::array<std::array<int, MAP_WIDTH>, MAP_HEIGHT> m_GameMap;
};