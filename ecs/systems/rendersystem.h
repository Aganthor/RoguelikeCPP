#pragma once

#include <entt/entity/registry.hpp>

namespace ecs {

class RenderSystem {
public:
    RenderSystem() = default;
    ~RenderSystem() = default;

    void render(entt::registry& ecsManager);

private:
};


} //namespace ecs
