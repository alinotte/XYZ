#include "Apple.h"
#include "Game.h"

namespace ApplesGame
{
	void InitApple(Apple& apple, const sf::Texture& texture)
	{
		apple.sprite.setTexture(texture);
		SetSpriteSize(apple.sprite, APPLE_SIZE, APPLE_SIZE);
		SetSpriteRelativeOrigin(apple.sprite, 0.5f, 0.5f);
	}

	void MarkAppleAsEaten(Apple& apple)
	{
		apple.isEaten = true;
	}

	void ResetApplePosition(Apple& apple)
	{
		apple.position.x = (float)(rand() % SCREEN_WIDTH);
		apple.position.y = (float)(rand() % SCREEN_HEIGHT);
		apple.isEaten = false;
	}

	Circle GetAppleCollider(const Apple& apple)
	{
		return { apple.position, APPLE_SIZE / 2.f };
	}

	void DrawApple(Apple& apple, sf::RenderWindow& window)
	{
		if (apple.isEaten)
		{
			return;
		}

		apple.sprite.setPosition(apple.position.x, apple.position.y);
		window.draw(apple.sprite);
	}
}
	
	


