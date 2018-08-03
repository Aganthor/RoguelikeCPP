#pragma once

#include <vector>
#include <memory>

#include <libtcod.hpp>

// Forward declare the Entity and CGameMap classes...
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

    void RenderAll(const std::vector<std::unique_ptr<Entity>>& entities, Map::CGameMap& game_map, bool fov_recompute);
    void ClearAll(const std::vector<std::unique_ptr<Entity>>& entities);

    void SetRenderSize(int w, int h) { m_Width = w; m_Height = h; }

private:
    int m_Width;
    int m_Height;
    
    //Consoles
	std::unique_ptr<TCODConsole> m_OffConsole;
};