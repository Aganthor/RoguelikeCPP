#include "Game.h"

#include "Engine.h"


Game::Game()
{
}


Game::~Game()
{
}

void Game::run()
{
	while (!TCODConsole::isWindowClosed() || m_Engine->isRunning())
	{
		m_Engine->HandleInput();
		if (!m_Engine->isRunning())
			break;
		m_Engine->Update();
	}
}

void Game::init()
{
	m_Engine = std::make_unique<Engine>();
	m_Engine->InitEngine();
}
