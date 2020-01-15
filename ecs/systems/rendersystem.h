#pragma once

#include <memory>

#include <libtcod/libtcod.hpp>
#include <entt/entity/registry.hpp>

namespace ecs {

class RenderSystem {
public:
    RenderSystem() = default;
    ~RenderSystem() = default;

    void setConsoleSize(int pWidth, int pHeight);
    void render(entt::registry& ecsManager);

private:
    int m_Width {0};
    int m_Height {0};
    std::unique_ptr<TCODConsole> m_OffConsole;
};


} //namespace ecs
