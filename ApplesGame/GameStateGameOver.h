#pragma once
#include "SFML/Graphics.hpp"

namespace ApplesGame
{
	struct Game;

	struct GameStateGameOverData
	{
		// resources
		sf::Font font;
	
		float timeSinceGameOver = 0.f;

		// ui data
		sf::Text gameOverText;
		sf::Text hintText;
		sf::Text recordsTableText;
	};

	// returns pointer to the allocated data
	void InitGameStateGameOver(GameStateGameOverData& data, Game& game);
	void HandleGameStateGameOverWindowEvent(GameStateGameOverData& data, Game& game, const sf::Event& event);
	void UpdateGameStateGameOver(GameStateGameOverData& data, Game& game, float timeDelta);
	void DrawGameStateGameOver(GameStateGameOverData& data, Game& game, sf::RenderWindow& window);
}