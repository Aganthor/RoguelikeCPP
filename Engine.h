#pragma once

#include <libtcod.hpp>
#include <memory>
#include <vector>
#include <tuple>
#include <string>

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

	enum class GameState 
	{
		PLAYERS_TURN,
		ENEMIES_TURN
	};

public:
	Engine();
	~Engine();

	void InitEngine();
	void Update();
    void HandleInput();
	void RegisterInput();

	bool isRunning() { return m_IsRunning; }
	bool isFullScreen() { return m_FullScreen; }

	void setGameState(GameState state) { m_GameState = state; }
    GameState getGameState(void) const { return m_GameState; }

	bool EntityPresentAt(int x, int y);
    void CreateEntity(int x, int y, const std::string& name, char display, TCODColor color, bool block = false, bool isPlayer = false);

    template <typename T, typename... TArgs>
    void CreateEntityTest(TArgs... mArgs)
    {
        auto uPtr(std::make_unique<T>(std::forward<TArgs>(mArgs)...));
        m_Entities.emplace(std::move(uPtr));
    }
	
private:
	void PlayersTurn();
	void EnemiesTurn();

    ecs::Entity* getPlayerEntity();
    ecs::Entity* getBlockingEntityAtLocation(int x, int y);
	
private:
	bool m_IsRunning = { false };
	bool m_FullScreen = { false };
	TCOD_key_t m_TCODKey;
	TCOD_mouse_t m_TCODMouse;
	TCOD_event_t m_TCODEvent;
	GameState m_GameState;

    std::vector<std::unique_ptr<ecs::Entity>> m_Entities;

	std::tuple<std::string, int, int> m_InputAction;

	Renderer m_Renderer;
	Map::CGameMap m_GameMap;
};

