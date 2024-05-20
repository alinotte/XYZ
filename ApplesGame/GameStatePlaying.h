#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Player.h"
#include "Apple.h"
#include "Rock.h"

namespace ApplesGame
{
	struct Game;

	struct GameStatePlayingData
	{
		// resources
		sf::Texture playerTexture;
		sf::Texture appleTexture;
		sf::Texture rockTexture;
		sf::SoundBuffer eatAppleSoundBuffer;
		sf::SoundBuffer gameOverSoundBuffer;
		sf::Font font;
		
		//objects
		sf::Sound deathSound;
		sf::Sound appleEatSound;
		
		// game data
		Player player;
		std::vector<Apple> apples;
		Rock rocks[NUM_ROCKS];
		int numEatenApples = 0;

		//ui data
		sf::Text scoreText;
		sf::Text inputHintText;
	};

	void InitGameStatePlaying(GameStatePlayingData& data, Game& game);
	void HandleGameStatePlayingWindowEvent(GameStatePlayingData& data, Game& game, const sf::Event& event);
	void UpdateGameStatePlaying(GameStatePlayingData& data, Game& game, float timeDelta);
	void DrawGameStatePlaying(GameStatePlayingData& data, Game& game, sf::RenderWindow& window);
}