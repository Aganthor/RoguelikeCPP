#include "Renderer.h"

#include <libtcod.hpp>

#include "ecs/Entity.h"

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}

void Renderer::RenderAll(const std::vector<std::unique_ptr<Entity>>& entities)
{
    for (auto &entity : entities)
    {
        TCODConsole::root->setDefaultForeground(entity->getColor());
        TCODConsole::root->putChar(entity->getXPos(), entity->getYPos(), entity->getVisual());
    }

    TCODConsole::flush();
}
    
void Renderer::ClearAll(const std::vector<std::unique_ptr<Entity>>& entities)
{

}