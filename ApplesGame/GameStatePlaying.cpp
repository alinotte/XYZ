#include "GameStatePlaying.h"
#include "Game.h"
#include <assert.h>

namespace ApplesGame
{
	int numApples = GetRandomIntinRange(MIN_APPLES, MAX_APPLES);

	void InitGameStatePlaying(GameStatePlayingData& data, Game& game)
	{
		// init game resources (terminate if error)
		assert(data.playerTexture.loadFromFile(RESOURCES_PATH + "\\Player.png"));
		assert(data.appleTexture.loadFromFile(RESOURCES_PATH + "\\Apple.png"));
		assert(data.rockTexture.loadFromFile(RESOURCES_PATH + "\\Rock.png"));
		assert(data.eatAppleSoundBuffer.loadFromFile(RESOURCES_PATH + "\\AppleEat.wav"));
		assert(data.font.loadFromFile(RESOURCES_PATH + "\\Fonts\\Roboto-Bold.ttf"));
		assert(data.gameOverSoundBuffer.loadFromFile(RESOURCES_PATH + "\\Death.wav"));

		// init game objects
		game.screenRect = { 0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT };

		// init player
		InitPlayer(data.player, data.playerTexture);
		SetPlayerPosition(data.player, { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f });
		SetPlayerSpeed(data.player, INITIAL_SPEED);
		SetPlayerDirection(data.player, playerDirection::Right);

		// init apples
		data.apples.clear();
		data.apples.resize(numApples);
		for (Apple& apple : data.apples)
		{
			InitApple(apple, data.appleTexture);
			ResetApplePosition(apple);
		}

		// init rocks
		for (Rock& rock : data.rocks)
		{
			InitRock(rock, data.rockTexture);
			ResetRockPosition(rock);
		}

		data.numEatenApples = 0;

		data.scoreText.setFont(data.font);
		data.scoreText.setCharacterSize(25);
		data.scoreText.setFillColor(sf::Color::White);
		data.scoreText.setString("Apples eaten: " + std::to_string(data.numEatenApples));

		data.inputHintText.setFont(data.font);
		data.inputHintText.setCharacterSize(25);
		data.inputHintText.setFillColor(sf::Color::White);
		data.inputHintText.setString("Press arrows to move, ESC to exit");

		data.appleEatSound.setBuffer(data.eatAppleSoundBuffer);
		data.deathSound.setBuffer(data.gameOverSoundBuffer);
	}

	void HandleGameStatePlayingWindowEvent(GameStatePlayingData& data, Game& game, const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				PushGameState(game, GameStateType::ExitDialog, false);
			}
		}
	}

	void UpdateGameStatePlaying(GameStatePlayingData& data, Game& game, float timeDelta)
	{
		// player movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			SetPlayerDirection(data.player, playerDirection::Right);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			SetPlayerDirection(data.player, playerDirection::Up);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			SetPlayerDirection(data.player, playerDirection::Left);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			SetPlayerDirection(data.player, playerDirection::Down);
		}

		// update player
		UpdatePlayer(data.player, timeDelta);

		// find player collision with apples
		data.apples.resize(numApples);
		for (Apple& apple : data.apples)
		{
			if (!apple.isEaten)
			{
				if (DoShapesCollide(GetPlayerCollider(data.player), GetAppleCollider(apple)))
				{
					if (game.options & UserGameSettings::InfiniteApples)
					{
						ResetApplePosition(apple);
					}
					else
					{
						MarkAppleAsEaten(apple);
					}

					if (game.options & UserGameSettings::WithAcceleration)
					{
						SetPlayerSpeed(data.player, GetPlayerSpeed(data.player) + ACCELERATION);
					}

					data.numEatenApples++;
					data.appleEatSound.play();
					data.scoreText.setString("Apples eaten: " + std::to_string(data.numEatenApples));
				}
			}
		}

		bool isGameFinished = (data.numEatenApples == data.apples.size())
			&& !((std::uint8_t)game.options & (std::uint8_t)UserGameSettings::InfiniteApples);

		// find player collision with rocks
		for (Rock& rock : data.rocks)
		{
			if (isGameFinished || DoShapesCollide(GetPlayerCollider(data.player), GetRockCollider(rock)))
			{
				PushGameState(game, GameStateType::GameOver, false);
				data.deathSound.play();
			}
		}

		// check screen border collision
		if (isGameFinished || !DoShapesCollide(GetPlayerCollider(data.player), game.screenRect))
		{
			PushGameState(game, GameStateType::GameOver, false);
			data.deathSound.play();
		}

		// we get player at index 0 so its always in the array
		game.recordsTable[0].name = "You";
		game.recordsTable[0].score = data.numEatenApples;


		//get fake competitors at indices 1 to 5
		for (int i = 1; i < MAX_RECORDS_TABLE_SIZE; ++i)
		{
			// set a random number of points and names on the leaderboard
			int score = GetRandomIntinRange(MIN_APPLES, MAX_APPLES);
			std::vector<std::string> randomNameArray = getRandomName(MAX_RECORDS_TABLE_SIZE);
			game.recordsTable[i].name = randomNameArray[i];
			game.recordsTable[i].score = score;
		}

		// sort records table
		std::sort(std::begin(game.recordsTable), std::end(game.recordsTable));
	}

	void DrawGameStatePlaying(GameStatePlayingData& data, Game& game, sf::RenderWindow& window)
	{
		// draw player
		DrawPlayer(data.player, window);

		// draw apples
		for (Apple& apple : data.apples)
		{
			DrawApple(apple, window);
		}

		// draw rocks
		for (auto& rock : data.rocks)
		{
			DrawRock(rock, window);
		}

		// draw ui
		data.scoreText.setPosition(20.f, 10.f);
		window.draw(data.scoreText);

		data.inputHintText.setPosition(SCREEN_WIDTH - data.inputHintText.getGlobalBounds().width - 20.f, 10.f);
		window.draw(data.inputHintText);
	}
}