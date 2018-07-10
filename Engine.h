#pragma once

#include <libtcod.hpp>
#include <memory>
#include <vector>

#include "ecs/Entity.h"
#include "Renderer.h"

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
	Engine() {};
	~Engine();

	void InitEngine();
	void Update();
	void HandleInput();

	bool isRunning() { return m_IsRunning; }
	bool isFullScreen() { return m_FullScreen; }

private:
	bool m_IsRunning = { false };
	bool m_FullScreen = { false };
	TCOD_key_t m_TCODKey;
	TCOD_mouse_t m_TCODMouse;
	TCOD_event_t m_TCODEvent;

	//Consoles
	TCOD_console_t m_MainConsole;
	TCOD_console_t m_OffConsole;

	std::unique_ptr<Entity> m_Player;
	std::vector<std::unique_ptr<Entity>> m_Entities;

	Renderer m_Renderer;
};

