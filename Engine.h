#pragma once

#include <libtcod.hpp>
#include <memory>
#include <vector>
#include <tuple>

#include "ecs/Entity.h"
#include "Renderer.h"
#include "MapObjects/GameMap.h"

//***************************************************************************//
// Engine code will be responsible for handling the graphics part of the     //
// game.                                                                     //
//***************************************************************************//

class Engine
{
public:
	const int SCREEN_WIDTH = 80;
	const int SCREEN_HEIGHT = 50;
	const int MAP_WIDTH = 80;
	const int MAP_HEIGHT = 45;

public:
	Engine();
	~Engine();

	void InitEngine();
	void Update();
	void RegisterInput();

	bool isRunning() { return m_IsRunning; }
	bool isFullScreen() { return m_FullScreen; }

private:
	void HandleInput();

private:
	bool m_IsRunning = { false };
	bool m_FullScreen = { false };
	TCOD_key_t m_TCODKey;
	TCOD_mouse_t m_TCODMouse;
	TCOD_event_t m_TCODEvent;

	std::vector<std::unique_ptr<Entity>> m_Entities;

	std::tuple<std::string, int, int> m_InputAction;

	Renderer m_Renderer;
	Map::CGameMap m_GameMap;
};

