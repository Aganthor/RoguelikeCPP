#include "Renderer.h"

#include <iostream>

#include <libtcod.hpp>

#include "ecs/Entity.h"
#include "MapObjects/GameMap.h"
#include "Engine.h"

Renderer::Renderer()
{
  m_OffConsole = std::make_unique<TCODConsole>(m_Width, m_Height);
}

Renderer::~Renderer()
{
}

void Renderer::RenderAll(const std::vector<std::unique_ptr<ecs::Entity>>& entities, Map::CGameMap& game_map,
			 bool fov_recompute)
{
    //First, render the map.
    auto height = game_map.getHeight();
    auto width  = game_map.getWidth();

    if (fov_recompute)
    {
        for (auto y = 0; y < height; ++y)
        {
            for (auto x = 0; x < width; ++x)
            {
                auto tile = game_map.getTile(x, y);

                if (bool in_fov = game_map.getFovMap()->isInFov(x, y); in_fov)
                {
                    if (tile.isBlockingSight())
                    {
                        m_OffConsole->setCharBackground(x, y, game_map.getColorCode("light_wall"));
                    }
                    else
                    {
                        m_OffConsole->setCharBackground(x, y, game_map.getColorCode("light_ground"));
                    }

                    game_map.getTile(x, y).setExplored();
                }
                else if (tile.isExplored())
                {
                    if (tile.isBlockingSight())
                    {
                        m_OffConsole->setCharBackground(x, y, game_map.getColorCode("dark_wall"));
                    }
                    else
                    {
                        m_OffConsole->setCharBackground(x, y, game_map.getColorCode("dark_ground"));
                    }
                }
            }
        }
    }

    //Second, render the entities.
    for (auto &entity : entities)
    {
        if (game_map.getFovMap()->isInFov(entity->getXPos(), entity->getYPos()))
        {
            m_OffConsole->setDefaultForeground(entity->getColor());
            m_OffConsole->putChar(entity->getXPos(), entity->getYPos(), entity->getVisual(), TCOD_BKGND_NONE);
        }
    }

    TCODConsole::blit(m_OffConsole.get(), 0, 0, width, height, TCODConsole::root, 0, 0);
    TCODConsole::flush();
}

void Renderer::ClearAll(const std::vector<std::unique_ptr<ecs::Entity>>& entities)
{
    for (auto &entity : entities)
        TCODConsole::root->putChar(entity->getXPos(), entity->getYPos(), ' ', TCOD_BKGND_NONE);
}
