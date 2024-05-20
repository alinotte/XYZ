#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Math.h"

namespace ApplesGame
{
	struct Game;

	struct Apple
	{
		bool isEaten = false;
		Position2D position;
		sf::Sprite sprite;
	};

	void InitApple(Apple& apple, const sf::Texture& texture);
	void MarkAppleAsEaten(Apple& apple);
	void ResetApplePosition(Apple& apple);
	Circle GetAppleCollider(const Apple& apple);
	void DrawApple(Apple& apple, sf::RenderWindow& window);
}



