#include <chrono>

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
    auto prevTime = std::chrono::system_clock::now();

	while (!TCODConsole::isWindowClosed() || m_Engine->isRunning())
	{
        auto time = std::chrono::system_clock::now();
        auto dt = std::chrono::duration<float>(time - prevTime).count();

		m_Engine->registerInput();
        m_Engine->handleInput();
		if (!m_Engine->isRunning())
			break;

        m_Engine->update(dt);

        prevTime = time;
	}
}

void Game::init()
{
	m_Engine = std::make_unique<Engine>();
	m_Engine->initEngine();
}
