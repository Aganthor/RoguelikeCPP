#include "Engine.h"

#include <algorithm>
#include <iostream>

#include "../Utility/Random.h"
#include "ecs/Fighter.h"

Engine::Engine()
{
	m_Renderer.SetRenderSize(MAP_WIDTH, MAP_HEIGHT);
}

Engine::~Engine()
{
}

///////////////////////////////////////////////////////////////////////////////
// Initialize TCOD consoles; create game map and place player in the 1st room.
///////////////////////////////////////////////////////////////////////////////
void Engine::InitEngine()
{
    //Initialize the random number generator.
	Random::init();

	TCODConsole::setCustomFont("res/fonts/arial10x10.png", TCOD_FONT_TYPE_GRAYSCALE | TCOD_FONT_LAYOUT_TCOD);
	TCODConsole::initRoot(SCREEN_WIDTH, SCREEN_HEIGHT, "Roguelike tutorial in C++", false, TCOD_RENDERER_OPENGL);

	m_GameMap.MakeMap(*this);
	m_GameMap.setRecomputeFov(true);

	//Place our player in the first room.
	auto [x, y] = m_GameMap.getFirstRoom().getCenter();
    CreateEntity(x, y, "Player", '@', TCODColor::white, false, true);
    //CreateEntityTest<Entity>

	m_IsRunning = true;
}

///////////////////////////////////////////////////////////////////////////////
// Called each loop to update the graphics part.
///////////////////////////////////////////////////////////////////////////////
void Engine::Update()
{
	if (m_GameMap.RecomputeFov())
	{
        //TODO Will need to be updated to new ECS...
		if (auto player = getPlayerEntity(); player)
		{
			m_GameMap.RecomputeFovMap(player->getXPos(), player->getYPos());
		}
	}
	m_Renderer.RenderAll(m_Entities, m_GameMap, m_GameMap.RecomputeFov());
	m_GameMap.setRecomputeFov(false);
	m_Renderer.ClearAll(m_Entities);
}

void Engine::HandleInput()
{
    PlayersTurn();
    EnemiesTurn();
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
		switch (m_TCODKey.c)
		{
		case 'y':
			m_InputAction = std::make_tuple("move", -1, -1);
			break;
		case 'u':
			m_InputAction = std::make_tuple("move", 1, -1);
			break;
		case 'b':
			m_InputAction = std::make_tuple("move", -1, 1);
			break;
		case 'n':
			m_InputAction = std::make_tuple("move", 1, 1);
			break;
		}

		//Check for Escape key or fullscreen sequence
        if (m_TCODKey.vk == TCODK_ESCAPE)
		{
			m_IsRunning = false;
		}
        if (m_TCODKey.vk == TCODK_ENTER && m_TCODKey.lalt)
		{
			m_FullScreen = !m_FullScreen;
			TCODConsole::setFullscreen(m_FullScreen);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// Helper function to determine if an entity is present at location x and y.
///////////////////////////////////////////////////////////////////////////////
bool Engine::EntityPresentAt(int x, int y)
{
	auto entity_present = std::find_if(m_Entities.begin(), m_Entities.end(), [x, y](const auto &entity)
	{
        //TODO Will need to be updated to new ECS...
		return entity->getXPos() == x && entity->getYPos() == y;
	});

	if (entity_present != std::end(m_Entities))
		return true;
	else
		return false;
}

///////////////////////////////////////////////////////////////////////////////
// Helper function to create a new entity for the game.
///////////////////////////////////////////////////////////////////////////////
void Engine::CreateEntity(int x, int y, const std::string& name, char display,
                          TCODColor color, bool block, bool isPlayer)
{
    if (isPlayer)
    {
        auto player = std::make_unique<ecs::Entity>(x, y, name, display, color, block);
        //TODO player stats should be saved and loaded from config file...
        //TODO Will need to be updated to new ECS...
        player->addComponent(std::make_unique<ecs::FighterComponent>(30, 2, 5));
        m_Entities.emplace_back(std::move(player));
    }
    else
    {
        m_Entities.emplace_back(std::make_unique<ecs::Entity>(x, y, name, display, color, block));
    }
}

///////////////////////////////////////////////////////////////////////////////
// Takes care of handling the input registered in RegisterInput.
///////////////////////////////////////////////////////////////////////////////
void Engine::PlayersTurn()
{
	auto [action, dx, dy] = m_InputAction;

    setGameState(GameState::PLAYERS_TURN);

	if ((action == "move") && (m_GameState == GameState::PLAYERS_TURN))
	{
		if (auto player = getPlayerEntity(); player)
		{
            //TODO Will need to be updated to new ECS...
			auto destination_x = player->getXPos() + dx;
			auto destination_y = player->getYPos() + dy;

			//Check to see if we can move...
			if (!m_GameMap.isBlocked(destination_x, destination_y))
			{
				if (auto target = getBlockingEntityAtLocation(destination_x, destination_y); target)
				{
					std::cout << "You kick the crap out of " << target->getName() << ", much to it's annoyance!\n";
				}
				else
				{
                    //TODO Will need to be updated to new ECS...
					player->Move(dx, dy);
					m_GameMap.setRecomputeFov(true);
				}
				setGameState(GameState::ENEMIES_TURN);
			}
		}
		//Reset the InputAction to nothing.
		m_InputAction = std::make_tuple("", 0, 0);
	}
}

///////////////////////////////////////////////////////////////////////////////
// Loops through all the entities and allowing them to take a turn.
///////////////////////////////////////////////////////////////////////////////
void Engine::EnemiesTurn()
{
	for (auto &entity : m_Entities)
	{
        //TODO Will need to be updated to new ECS...
		if (entity->getName() != "Player")
		{
            std::cout << "The " << entity->getName() << " ponders the meaning of its existence.\n";
		}
	}

	setGameState(GameState::PLAYERS_TURN);
}

///////////////////////////////////////////////////////////////////////////////
// Helper function to get the player Entity!
///////////////////////////////////////////////////////////////////////////////
ecs::Entity* Engine::getPlayerEntity()
{
	auto player = std::find_if(m_Entities.begin(), m_Entities.end(), [](const auto &entity)
	{
        //TODO Will need to be updated to new ECS...
		return entity->getName() == "Player";
	});

	if (player != std::end(m_Entities))
		return (*player).get();
	else
		return nullptr;
}

///////////////////////////////////////////////////////////////////////////////
// Helper function to determine if the entity we are about to walk to is
// a blocking entity or not.
///////////////////////////////////////////////////////////////////////////////
ecs::Entity* Engine::getBlockingEntityAtLocation(int x, int y)
{
	auto ent = std::find_if(m_Entities.begin(), m_Entities.end(), [x, y](const auto &entity)
	{
        //TODO Will need to be updated to new ECS...
		return entity->getXPos() == x && entity->getYPos() == y;
	});

	if (ent != std::end(m_Entities))
	{
        //TODO Will need to be updated to new ECS...
		if ((*ent)->isBlocking())
			return (*ent).get();
		else
			return nullptr;
	}

	//If no entities at location, that means that it's certainly not blocking :)
	return nullptr;
}
