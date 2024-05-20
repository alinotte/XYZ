#include <SFML/Graphics.hpp>
#include "Game.h"

using namespace ApplesGame;

int main()
{
	// init random number generator
	unsigned int seed = (unsigned int)time(nullptr);
	srand(seed);

	// init window
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples Game!");
	
	// init game (we now use too much memory for stack, so we need to allocate it on heap
	ApplesGame::Game* game = new ApplesGame::Game();
	InitGame(*game);
	
	// init game clocks
	sf::Clock gameClock;
	sf::Time lastTime = gameClock.getElapsedTime();
		
	// game loop
	while (window.isOpen())
	{
		// reduce framerate not to spam CPU and GPU
		sf::sleep(sf::milliseconds(16));

		HandleWindowEvents(*game, window);

		if (!window.isOpen())
		{
			break;
		}

		// calculate time delta
		sf::Time currentTime = gameClock.getElapsedTime();
		float timeDelta = currentTime.asSeconds() - lastTime.asSeconds();
		lastTime = currentTime;
		if (UpdateGame(*game, timeDelta))
		{
			// render game
			window.clear();
			DrawGame(*game, window);
			window.display();
		}
		else
		{
			window.close();
		}		
	}

	// deinitialisation
	ShutdownGame(*game);
	delete game;
	game = nullptr;
		
	return 0;
}
