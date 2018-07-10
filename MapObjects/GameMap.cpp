#include "GameMap.h"

CGameMap::CGameMap() : m_Width { 0 }, m_Height { 0 }
{
}

CGameMap::CGameMap(int w, int h) : m_Width { w }, m_Height { h }
{
    InitTiles();
}

void CGameMap::InitTiles(void)
{
    
}