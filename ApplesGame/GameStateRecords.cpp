#include "GameStateRecords.h"
#include <assert.h>
#include "Game.h"

namespace ApplesGame
{
	void InitGameStateRecords(GameStateRecordsData& data, Game& game)
	{
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		data.recordsTableText.setFont(data.font);
		data.recordsTableText.setCharacterSize(24);
		data.recordsTableText.setFillColor(sf::Color::Green);
		data.recordsTableText.setOrigin(GetItemOrigin(data.recordsTableText, { 0.5f, 0.f }));

		data.background.setFillColor(sf::Color::Black);
	}

	void UpdateGameStateRecords(GameStateRecordsData& data, Game& game, float timeDelta)
	{
		data.recordsTableText.setString("Records:");
		for (int i = 0; i < MAX_RECORDS_TABLE_SIZE - 1; ++i)
		{
			data.recordsTableText.setString(data.recordsTableText.getString() + "\n" + game.recordsTable[i].name + ": " + std::to_string(game.recordsTable[i].score));
		}
		data.recordsTableText.setOrigin(GetItemOrigin(data.recordsTableText, { 0.5f, 0.f }));
	}

	void HandleGameStateRecordsWindowEvent(GameStateRecordsData& data, Game& game, const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				SwitchGameState(game, GameStateType::MainMenu);
			}
		}
	}

	void DrawGameStateRecords(GameStateRecordsData& data, Game& game, sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = window.getView().getSize();

		data.recordsText.setPosition(viewSize.x / 2.f, viewSize.y / 2.f);
		window.draw(data.recordsText);

		data.recordsTableText.setPosition(viewSize.x / 2.f, 30.f);
		window.draw(data.recordsTableText);
	}
}