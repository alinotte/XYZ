#pragma once
#include "SFML/Graphics.hpp"

namespace ApplesGame
{
	struct Game;

	struct GameStateRecordsData
	{
		// resources
		sf::Font font;

		// objects
		sf::RectangleShape background;

		// ui data
		sf::Text recordsText;
		sf::Text recordsTableText;
	};
	void InitGameStateRecords(GameStateRecordsData& data, Game& game);
	void UpdateGameStateRecords(GameStateRecordsData& data, Game& game, float timeDelta);
	void HandleGameStateRecordsWindowEvent(GameStateRecordsData& data, Game& game, const sf::Event& event);
	void DrawGameStateRecords(GameStateRecordsData& data, Game& game, sf::RenderWindow& window);
}