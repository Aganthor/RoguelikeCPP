#include "rendersystem.h"
#include "../components/asciicomponent.h"
#include "../components/positioncomponent.h"

namespace ecs {

void RenderSystem::render(entt::registry& ecsManager) {
    //Iterate all entities that have the asciicomponent...
    const auto view = ecsManager.view<AsciiComponent, PositionComponent>();
    for (const entt::entity e : view) {
    }
}

}
