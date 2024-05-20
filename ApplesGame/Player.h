#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Math.h"

namespace ApplesGame
{
	struct Game;

	enum class playerDirection
	{
		Right = 0,
		Up,
		Left,
		Down
	};

	struct Player
	{
		Position2D position;
		float speed = INITIAL_SPEED;
		playerDirection direction = playerDirection::Right;
		sf::Sprite sprite;
	};

	void InitPlayer(Player& player, const sf::Texture& texture);
	void SetPlayerDirection(Player& player, playerDirection direction);
	void SetPlayerPosition(Player& player, const Position2D& position);
	void SetPlayerSpeed(Player& player, float speed);
	float GetPlayerSpeed(const Player& player);
	Rectangle GetPlayerCollider(const Player& player);
	void UpdatePlayer(Player& player, float deltaTime);
	void DrawPlayer(Player& player, sf::RenderWindow& window);

}



