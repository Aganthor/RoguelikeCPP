#pragma once

#include <vector>
#include <memory>

// Forward declare the Entity class...
class Entity;
namespace Map
{
    class CGameMap;
}

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void RenderAll(const std::vector<std::unique_ptr<Entity>>& entities, const Map::CGameMap& game_map);
    void ClearAll(const std::vector<std::unique_ptr<Entity>>& entities);
};