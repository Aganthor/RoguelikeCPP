#include "Renderer.h"

#include <iostream>

#include <libtcod.hpp>

#include "ecs/Entity.h"
#include "MapObjects/GameMap.h"
#include "Engine.h"

Renderer::Renderer()
{
    m_MainConsole = std::make_unique<TCODConsole>(m_Width, m_Height);
	//m_OffConsole = std::make_unique<TCODConsole>(m_Width, m_Height);
}

Renderer::~Renderer()
{
    std::cout << "Deleting renderer...\n";
}

void Renderer::RenderAll(const std::vector<std::unique_ptr<Entity>>& entities, const Map::CGameMap& game_map)
{
    //First, render the map.
    auto height = game_map.getHeight();
    auto width  = game_map.getWidth();
    for (auto y = 0; y < height; ++y)
    {
        for (auto x = 0; x < width; ++x)
        {
            auto tile = game_map.getTile(x, y);
            if (tile.isBlockingSight())
            {
                m_MainConsole->setCharBackground(x, y, game_map.getColorCode("dark_wall"));
            }
            else
            {
                m_MainConsole->setCharBackground(x, y, game_map.getColorCode("dark_ground"));
            }
        }
    }

    //Second, render the entities.
    for (auto &entity : entities)
    {
        m_MainConsole->setDefaultForeground(entity->getColor());
        m_MainConsole->putChar(entity->getXPos(), entity->getYPos(), entity->getVisual(), TCOD_BKGND_NONE);
    }

    TCODConsole::blit(m_MainConsole.get(), 0, 0, width, height, TCODConsole::root, 0, 0);
    TCODConsole::flush();
}
    
void Renderer::ClearAll(const std::vector<std::unique_ptr<Entity>>& entities)
{
    for (auto &entity : entities)
        TCODConsole::root->putChar(entity->getXPos(), entity->getYPos(), ' ', TCOD_BKGND_NONE);
}