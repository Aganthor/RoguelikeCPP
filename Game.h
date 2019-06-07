#pragma once

#include <memory>

class Engine;

// Main game class.

class Game
{
public:
	Game();
	~Game();

	//Main game loop.
	void run();

	void init();

private:
	std::unique_ptr<Engine> m_Engine;

};

