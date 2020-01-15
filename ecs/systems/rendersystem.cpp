#include "rendersystem.h"
#include "../components/asciicomponent.h"
#include "../components/positioncomponent.h"

namespace ecs {

void RenderSystem::setConsoleSize(int pWidth, int pHeight) {
    assert(pWidth > 0 && pHeight > 0);
    m_Width = pWidth;
    m_Height = pHeight;
    m_OffConsole = std::make_unique<TCODConsole>(m_Width, m_Height);
}

void RenderSystem::render(entt::registry& ecsManager) {
    //Iterate all entities that have the asciicomponent...
    const auto view = ecsManager.view<AsciiComponent, PositionComponent>();

    for (const entt::entity e : view) {  
        const auto ascii = view.get<AsciiComponent>(e);
        const auto pos = view.get<PositionComponent>(e);

        m_OffConsole->setDefaultForeground(ascii.color);
        m_OffConsole->putChar(pos.x, pos.y, ascii.character, TCOD_BKGND_NONE);

        TCODConsole::blit(m_OffConsole.get(), 0, 0, m_Width, m_Height, TCODConsole::root, 0, 0);
        TCODConsole::flush();
    }
}

}
