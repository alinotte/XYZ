#include "Rock.h"
#include "Game.h"

namespace ApplesGame
{
	void InitRock(Rock& rock, const sf::Texture& texture)
	{
		rock.sprite.setTexture(texture);
		SetSpriteSize(rock.sprite, ROCK_SIZE, ROCK_SIZE);
		SetSpriteRelativeOrigin(rock.sprite, 0.5f, 0.5f);
	}

	void ResetRockPosition(Rock& rock)
	{
		rock.position.x = (float)(rand() % SCREEN_WIDTH);
		rock.position.y = (float)(rand() % SCREEN_HEIGHT);
	}

	Rectangle GetRockCollider(const Rock& rock)
	{
		return { { rock.position.x - ROCK_SIZE / 2.f, rock.position.y - ROCK_SIZE / 2.f },
					{ ROCK_SIZE, ROCK_SIZE } };
	}

	void DrawRock(Rock& rock, sf::RenderWindow& window)
	{
		rock.sprite.setPosition(rock.position.x, rock.position.y);
		window.draw(rock.sprite);
	}
}
