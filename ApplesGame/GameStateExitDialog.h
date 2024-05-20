#pragma once
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
	struct Game;

	struct GameStateExitDialogData
	{
		sf::Font font;

		sf::RectangleShape background;
		sf::Text hintText;
	};

	void InitGameStateExitDialog(GameStateExitDialogData& data, Game& game);
	void HandleGameStateExitDialogWindowEvent(GameStateExitDialogData& data, Game& game, const sf::Event& event);
	void DrawGameStateExitDialog(GameStateExitDialogData& data, Game& game, sf::RenderWindow& window);
}
