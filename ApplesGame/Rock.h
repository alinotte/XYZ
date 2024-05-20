#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Math.h"

namespace ApplesGame
{
	struct Game;

	struct Rock
	{
		Position2D position;
		sf::Sprite sprite;
	};

	void InitRock(Rock& rock, const sf::Texture& texture);
	void ResetRockPosition(Rock& rock);
	Rectangle GetRockCollider(const Rock& rock);
	void DrawRock(Rock& rock, sf::RenderWindow& window);
}
	

