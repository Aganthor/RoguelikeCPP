#include "Engine.h"

Engine::~Engine()
{
	TCOD_console_delete(m_MainConsole);
	TCOD_console_delete(m_OffConsole);
}

void Engine::InitEngine()
{
	TCODConsole::setCustomFont("res/fonts/arial10x10.png", TCOD_FONT_TYPE_GRAYSCALE | TCOD_FONT_LAYOUT_TCOD);
	TCODConsole::initRoot(80, 50, "Roguelike tutorial in C++", false);
	
	m_MainConsole = TCOD_console_new(Engine::MAP_WIDTH, Engine::MAP_HEIGHT);
	m_OffConsole = TCOD_console_new(Engine::MAP_WIDTH, Engine::MAP_HEIGHT);

	m_Player = std::make_unique<Entity>(0, 0, "Player", '@', TCODColor::white);

	m_IsRunning = true;
}

void Engine::Update()
{
	//TCOD_color_t col;
	//TCODColor col2;
	//TCOD_console_set_default_foreground(m_MainConsole, TCODColor::white);
	TCODConsole::root->setDefaultForeground(TCODColor::white);
	TCODConsole::root->clear();
	TCODConsole::root->putChar(m_Player->getXPos(), m_Player->getYPos(), m_Player->getVisual());
	//TCODConsole::blit(m_MainConsole, 0, 0, Engine::MAP_WIDTH, Engine::MAP_HEIGHT, 0, 0, 0);
	TCODConsole::flush();
}

void Engine::HandleInput()
{
	m_TCODEvent = TCODSystem::checkForEvent(TCOD_EVENT_KEY | TCOD_EVENT_MOUSE, &m_TCODKey, &m_TCODMouse);

	//Handle character mouvement
	switch (m_TCODKey.vk)
	{
	case TCODK_UP:
		m_Player->Move(0, -1);
		break;
	case TCODK_DOWN:
		m_Player->Move(0, 1);
		break;
	case TCODK_LEFT:
		m_Player->Move(-1, 0);
		break;
	case TCODK_RIGHT:
		m_Player->Move(1, 0);
		break;
	}

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


