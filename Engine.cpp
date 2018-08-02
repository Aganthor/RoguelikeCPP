#include "Engine.h"

#include <algorithm>
//#include <iostream>

#include "../Utility/Random.h"

using namespace Map;

Engine::Engine()
{
	m_Renderer.SetRenderSize(MAP_WIDTH, MAP_HEIGHT);
}

Engine::~Engine()
{
}

///////////////////////////////////////////////////////////////////////////////
// Initialize TCOD consoles.
///////////////////////////////////////////////////////////////////////////////
void Engine::InitEngine()
{
    //Initialize the random number generator.
	Random::init();

	TCODConsole::setCustomFont("res/fonts/arial10x10.png", TCOD_FONT_TYPE_GRAYSCALE | TCOD_FONT_LAYOUT_TCOD);
	TCODConsole::initRoot(SCREEN_WIDTH, SCREEN_HEIGHT, "Roguelike tutorial in C++", false);//, TCOD_RENDERER_OPENGL);

	m_GameMap.MakeMap();
	m_GameMap.setRecomputeFov(true);

	//Place our player in the first room.
	auto [x, y] = m_GameMap.getFirstRoom().getCenter();
	m_Entities.push_back(std::make_unique<Entity>(x, y, "Player", '@', TCODColor::white));

	m_IsRunning = true;
}

///////////////////////////////////////////////////////////////////////////////
// Called each loop to update the graphics part.
///////////////////////////////////////////////////////////////////////////////
void Engine::Update()
{
	if (m_GameMap.RecomputeFov())
	{
		auto player = getPlayerEntity();
		if (player)
		{
			m_GameMap.RecomputeFovMap(player->getXPos(), player->getYPos());
		}
	}
	m_Renderer.RenderAll(m_Entities, m_GameMap, m_GameMap.RecomputeFov());
	m_GameMap.setRecomputeFov(false);
	m_Renderer.ClearAll(m_Entities);
}

///////////////////////////////////////////////////////////////////////////////
// Function that register keyboard input. FOr fullscreen and exit, we just
// set some boolean. FOr mouvement, we set up the m_InputAction tuple to
// represent what the user did.
///////////////////////////////////////////////////////////////////////////////
void Engine::RegisterInput()
{
	m_TCODEvent = TCODSystem::checkForEvent(TCOD_EVENT_KEY | TCOD_EVENT_MOUSE, &m_TCODKey, &m_TCODMouse);

	//Handle character mouvement
	if (m_TCODEvent == TCOD_EVENT_KEY_PRESS)
	{
		switch (m_TCODKey.vk)
		{
		case TCODK_UP:
			m_InputAction = std::make_tuple("move", 0, -1);
			break;
		case TCODK_DOWN:
			m_InputAction = std::make_tuple("move", 0, 1);
			break;
		case TCODK_LEFT:
			m_InputAction = std::make_tuple("move", -1, 0);
			break;
		case TCODK_RIGHT:
			m_InputAction = std::make_tuple("move", 1, 0);
			break;
		}

		HandleInput();

		//Check for Escape key or fullscreen sequence
		if (m_TCODKey.vk == TCODK_ESCAPE)
		{
			m_IsRunning = false;
		}
		else if (m_TCODKey.vk == TCODK_ENTER && m_TCODKey.lalt)
		{
			m_FullScreen = !m_FullScreen;
			TCODConsole::setFullscreen(m_FullScreen);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// Takes care of handling the input registered in RegisterInput.
///////////////////////////////////////////////////////////////////////////////
void Engine::HandleInput()
{
	auto [action, dx, dy] = m_InputAction;

	if (action == "move")
	{
		auto player = getPlayerEntity();

		if (player)
		{
			//Check to see if we can move...
			if (!m_GameMap.isBlocked(player->getXPos() + dx, player->getYPos() + dy))
			{
				player->Move(dx, dy);
				m_GameMap.setRecomputeFov(true);
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// Helper function to get the player Entity!
///////////////////////////////////////////////////////////////////////////////
Entity* Engine::getPlayerEntity()
{
	auto player = std::find_if(m_Entities.begin(), m_Entities.end(), [](const auto &entity)
	{
		return entity->getName() == "Player";
	});

	if (player != std::end(m_Entities))
		return (*player).get();
	else
		return nullptr;

	return nullptr;
}


