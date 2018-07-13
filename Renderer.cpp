#include "Renderer.h"

#include <libtcod.hpp>

#include "ecs/Entity.h"
#include "MapObjects/GameMap.h"

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}

void Renderer::RenderAll(const std::vector<std::unique_ptr<Entity>>& entities, const Map::CGameMap& game_map)
{
    //First, render the map.
    auto height = game_map.getHeight();
    auto width  = game_map.getWidth();
    for (auto x = 0; x <= width; ++x)
    {
        for (auto y = 0; y <= height; ++y)
        {
            auto wall = game_map.getTile(x, y);
            /*if (wall.isBlockingSight())
                TCODConsole::root->setCharBackground(y, x, game_map.getColorCode("dark_wall"), TCOD_BKGND_SET);
            else
                TCODConsole::root->setCharBackground(y, x, game_map.getColorCode("dark_ground"), TCOD_BKGND_SET);            
                */
            if (wall.isBlockingSight())
                TCODConsole::root->setCharBackground(x, y, game_map.getColorCode("dark_wall"), TCOD_BKGND_SET);
            else
                TCODConsole::root->setCharBackground(x, y, game_map.getColorCode("dark_ground"), TCOD_BKGND_SET);
        }
    }

    //Second, render the entities.
    for (auto &entity : entities)
    {
        TCODConsole::root->setDefaultForeground(entity->getColor());
        TCODConsole::root->putChar(entity->getXPos(), entity->getYPos(), entity->getVisual(), TCOD_BKGND_NONE);
    }

    TCODConsole::flush();
}
    
void Renderer::ClearAll(const std::vector<std::unique_ptr<Entity>>& entities)
{
    for (auto &entity : entities)
    {
        TCODConsole::root->putChar(entity->getXPos(), entity->getYPos(), ' ', TCOD_BKGND_NONE);
    }
}