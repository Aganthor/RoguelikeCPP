#pragma once

#include <vector>
#include <memory>

// Forward declare the Entity class...
class Entity;

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void RenderAll(const std::vector<std::unique_ptr<Entity>>& entities);
    void ClearAll(const std::vector<std::unique_ptr<Entity>>& entities);

private:
    void DrawEntity(const Entity& entity);
    void ClearEntity(const Entity& Entity);
};