#pragma once

#include <libtcod.hpp>
#include <memory>
#include <vector>
#include <tuple>
#include <string>

#include "Renderer.h"
#include "MapObjects/GameMap.h"
#include "ecs/entitymanager.h"


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

    static constexpr auto ComponentCount = 32;
    static constexpr auto SystemCount = 8;

	enum class GameState 
	{
		PLAYERS_TURN,
		ENEMIES_TURN
	};

public:
    Engine();
	~Engine();

	void InitEngine();
    void Update(float dt);
    void HandleInput();
	void RegisterInput();

	bool isRunning() { return m_IsRunning; }
	bool isFullScreen() { return m_FullScreen; }

	void setGameState(GameState state) { m_GameState = state; }
    GameState getGameState(void) const { return m_GameState; }

	bool EntityPresentAt(int x, int y);
    void CreateEntity(int x, int y, const std::string& name, char display, TCODColor color, bool block = false, bool isPlayer = false);

private:
    void setupEntityManager();
	void PlayersTurn();
	void EnemiesTurn();

//    ecs::Entity* getPlayerEntity();
//    ecs::Entity* getBlockingEntityAtLocation(int x, int y);
	
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
    //std::unique_ptr<ecs::EntityManager<ComponentCount, SystemCount>> m_entityManager;
    ecs::EntityManager<ComponentCount, SystemCount> m_entityManager;
};

