#pragma once

#include <memory>
#include <vector>
#include <tuple>
#include <string>

#include <libtcod/libtcod.hpp>

#include "Renderer.h"
#include "MapObjects/GameMap.h"
#include <entt/entt.hpp>


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

    const std::size_t MAX_ENTITY = 1000;

	enum class GameState 
	{
		PLAYERS_TURN,
		ENEMIES_TURN
	};

public:
    Engine();
	~Engine();

    void initEngine();
    void update(float dt);
    void handleInput();
    void registerInput();

	bool isRunning() { return m_IsRunning; }
	bool isFullScreen() { return m_FullScreen; }

	void setGameState(GameState state) { m_GameState = state; }
    GameState getGameState(void) const { return m_GameState; }

    bool entityPresentAt(int x, int y);
    void createEntity(int x, int y, const std::string& name, char display, TCODColor color, bool block = false, bool isPlayer = false);

private:
    void setupEntityManager();
    void playersTurn();
    void enemiesTurn();
	
private:
	bool m_IsRunning = { false };
	bool m_FullScreen = { false };
	TCOD_key_t m_TCODKey;
	TCOD_mouse_t m_TCODMouse;
	TCOD_event_t m_TCODEvent;
	GameState m_GameState;

    std::tuple<std::string, int, int> m_InputAction{};

	Renderer m_Renderer;
	Map::CGameMap m_GameMap;

    entt::registry m_ecsManager;
};

