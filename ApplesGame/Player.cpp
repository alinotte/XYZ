#include "Player.h"
#include "Game.h"

namespace ApplesGame
{
	void InitPlayer(Player& player, const sf::Texture& texture)
	{
		// init player state
		player.position = { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f };
		player.speed = INITIAL_SPEED;
		player.direction = playerDirection::Right;

		// init player sprite
		player.sprite.setTexture(texture);
		SetSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
		SetSpriteRelativeOrigin(player.sprite, 0.5f, 0.5f);
	}

	void SetPlayerDirection(Player& player, playerDirection direction)
	{
		player.direction = direction;
	}

	void SetPlayerPosition(Player& player, const Position2D& position)
	{
		player.position = position;
	}

	void SetPlayerSpeed(Player& player, float speed)
	{
		player.speed = speed;
	}

	float GetPlayerSpeed(const Player& player)
	{
		return player.speed;
	}

	Rectangle GetPlayerCollider(const Player& player)
	{
		return { { player.position.x - PLAYER_SIZE / 2.f, player.position.y - PLAYER_SIZE / 2.f },
			{ PLAYER_SIZE, PLAYER_SIZE } };
	}

	void UpdatePlayer(Player& player, float deltaTime)
	{
		// move player
		switch (player.direction)
		{
		case playerDirection::Right:
		{
			player.position.x += player.speed * deltaTime;
			break;
		}
		case playerDirection::Up:
		{
			player.position.y -= player.speed * deltaTime;
			break;
		}
		case playerDirection::Left:
		{
			player.position.x -= player.speed * deltaTime;
			break;
		}
		case playerDirection::Down:
		{
			player.position.y += player.speed * deltaTime;
			break;
		}
		}
	}

	void DrawPlayer(Player& player, sf::RenderWindow& window)
	{
		player.sprite.setPosition(player.position.x, player.position.y);
		
		if (player.direction == playerDirection::Left)
		{
			SetSpriteSize(player.sprite, -PLAYER_SIZE, PLAYER_SIZE);
			player.sprite.setRotation(0.f);
		}
		else
		{
			SetSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
			player.sprite.setRotation((float)player.direction * -90.f);
		}

		window.draw(player.sprite);
	}
}



