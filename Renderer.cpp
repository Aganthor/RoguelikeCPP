#include "Renderer.h"

#include <libtcod.hpp>

#include "ecs/Entity.h"
#include "MapObjects/GameMap.h"
#include "Engine.h"

Renderer::Renderer()
{
    //m_MainConsole = TCOD_console_new(m_Width, m_Height);
    std::make_unique<TCODConsole>(m_Width, m_Height);
	//m_OffConsole = TCOD_console_new(m_Width, m_Height);
}

Renderer::~Renderer()
{
	//TCOD_console_delete(m_MainConsole);
	//TCOD_console_delete(m_OffConsole);
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
            auto wall = game_map.getTile(x, y);
            if (wall.isBlockingSight())
                //TCOD_console_set_char_background(m_MainConsole, x, y, game_map.getColorCode("dark_wall"), TCOD_BKGND_SET);
                //TCODConsole::setCharBackground()
                m_MainConsole->setCharBackground(x, y, game_map.getColorCode("dark_wall"));
            else
                //TCOD_console_set_char_background(m_MainConsole, x, y, game_map.getColorCode("dark_ground"), TCOD_BKGND_SET);
                m_MainConsole->setCharBackground(x, y, game_map.getColorCode("dark_ground"));
        }
    }

    //Second, render the entities.
    for (auto &entity : entities)
    {
        m_MainConsole->setDefaultForeground(entity->getColor());
        m_MainConsole->putChar(entity->getXPos(), entity->getYPos(), entity->getVisual(), TCOD_BKGND_NONE);
        //TCOD_console_set_default_foreground(m_MainConsole, entity->getColor());
        //TCOD_console_put_char(m_MainConsole, entity->getXPos(), entity->getYPos(), entity->getVisual(), TCOD_BKGND_NONE);
    }

    //TCOD_console_blit(m_MainConsole, 0, 0, 0, 0, TCODConsole::root, 0, 0, 0, 0);
    TCODConsole::blit(m_MainConsole.get(), 0, 0, width, height, TCODConsole::root, 0, 0);
    TCODConsole::flush();
}
    
void Renderer::ClearAll(const std::vector<std::unique_ptr<Entity>>& entities)
{
    for (auto &entity : entities)
        TCODConsole::root->putChar(entity->getXPos(), entity->getYPos(), ' ', TCOD_BKGND_NONE);
}