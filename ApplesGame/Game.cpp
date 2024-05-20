#include "Game.h"
#include <assert.h>
#include <algorithm>
#include "GameStatePlaying.h"
#include "GameStateGameOver.h"
#include "GameStateExitDialog.h"
#include "GameStateMainMenu.h"
#include "GameStateRecords.h"

namespace ApplesGame
{
	bool operator<(const RecordsTableItem& lhs, const RecordsTableItem& rhs)
	{
		return lhs.score > rhs.score;
	}

	void InitGame(Game& game)
	{
		game.gameStateChangeType = GameStateChangeType::None;
		game.pendingGameStateType = GameStateType::None;
		game.pendingGameStateIsExclusivelyVisible = false;
		SwitchGameState(game, GameStateType::MainMenu);
	}

	void HandleWindowEvents(Game& game, sf::RenderWindow& window)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// close window if close button pressed
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (game.gameStateStack.size() > 0)
			{
				HandleWindowEventGameState(game, game.gameStateStack.back(), event);
			}
		}
	}

	bool UpdateGame(Game& game, float timeDelta)
	{
		if (game.gameStateChangeType == GameStateChangeType::Switch)
		{
			// shutdown all game states
			while (game.gameStateStack.size() > 0)
			{
				ShutdownGameState(game, game.gameStateStack.back());
				game.gameStateStack.pop_back();
			}
		}
		else if (game.gameStateChangeType == GameStateChangeType::Pop)
		{
			// shutdown only current game state
			if (game.gameStateStack.size() > 0)
			{
				ShutdownGameState(game, game.gameStateStack.back());
				game.gameStateStack.pop_back();
			}
		}

		// initialize new game state if needed
		if (game.pendingGameStateType != GameStateType::None)
		{
			game.gameStateStack.push_back({ game.pendingGameStateType, nullptr, game.pendingGameStateIsExclusivelyVisible });
			InitGameState(game, game.gameStateStack.back());
		}

		game.gameStateChangeType = GameStateChangeType::None;
		game.pendingGameStateType = GameStateType::None;
		game.pendingGameStateIsExclusivelyVisible = false;

		if (game.gameStateStack.size() > 0)
		{
			UpdateGameState(game, game.gameStateStack.back(), timeDelta);
			return true;
		}

		return false;
	}

	void DrawGame(Game& game, sf::RenderWindow& window)
	{
		if (game.gameStateStack.size() > 0)
		{
			std::vector<GameState*> visibleGameStates;
			for (auto it = game.gameStateStack.rbegin(); it != game.gameStateStack.rend(); ++it)
			{
				visibleGameStates.push_back(&(*it));
				if (it->isExclusivelyVisible)
				{
					break;
				}
			}

			for (auto it = visibleGameStates.rbegin(); it != visibleGameStates.rend(); ++it)
			{
				DrawGameState(game, **it, window);
			}
		}
	}

	void ShutdownGame(Game& game)
	{
		// shutdown all game states
		while (game.gameStateStack.size() > 0)
		{
			ShutdownGameState(game, game.gameStateStack.back());
			game.gameStateStack.pop_back();
		}

		game.gameStateChangeType = GameStateChangeType::None;
		game.pendingGameStateType = GameStateType::None;
		game.pendingGameStateIsExclusivelyVisible = false;
	}

	void PushGameState(Game& game, GameStateType stateType, bool isExclusivelyVisible)
	{
		game.pendingGameStateType = stateType;
		game.pendingGameStateIsExclusivelyVisible = isExclusivelyVisible;
		game.gameStateChangeType = GameStateChangeType::Push;
	}

	void PopGameState(Game& game)
	{
		game.pendingGameStateType = GameStateType::None;
		game.pendingGameStateIsExclusivelyVisible = false;
		game.gameStateChangeType = GameStateChangeType::Pop;
	}

	void SwitchGameState(Game& game, GameStateType newState)
	{
		game.pendingGameStateType = newState;
		game.pendingGameStateIsExclusivelyVisible = false;
		game.gameStateChangeType = GameStateChangeType::Switch;
	}

	void InitGameState(Game& game, GameState& state)
	{
		switch (state.type)
		{
		case GameStateType::MainMenu:
		{
			state.data = new GameStateMainMenuData();
			InitGameStateMainMenu(*(GameStateMainMenuData*)state.data, game);
			break;
		}
		case GameStateType::Playing:
		{
			state.data = new GameStatePlayingData();
			InitGameStatePlaying(*(GameStatePlayingData*)state.data, game);
			break;
		}
		case GameStateType::GameOver:
		{
			state.data = new GameStateGameOverData();
			InitGameStateGameOver(*(GameStateGameOverData*)state.data, game);
			break;
		}
		case GameStateType::ExitDialog:
		{
			state.data = new GameStateExitDialogData();
			InitGameStateExitDialog(*(GameStateExitDialogData*)state.data, game);
			break;
		}
		case GameStateType::Records:
		{
			state.data = new GameStateRecordsData();
			InitGameStateRecords(*(GameStateRecordsData*)state.data, game);
			break;
		}
		default:
			assert(false); // we want to know if we forgot to implement new game state
			break;
		}
	}

	void ShutdownGameState(Game& game, GameState& state)
	{
		switch (state.type)
		{
		case GameStateType::MainMenu:
		{
			delete (GameStateMainMenuData*)state.data;
			break;
		}
		case GameStateType::Playing:
		{
			delete (GameStatePlayingData*)state.data;
			break;
		}
		case GameStateType::GameOver:
		{
			delete (GameStateGameOverData*)state.data;
			break;
		}
		case GameStateType::ExitDialog:
		{
			delete (GameStateExitDialogData*)state.data;
			break;
		}
		case GameStateType::Records:
		{
			delete (GameStateRecordsData*)state.data;
			break;
		}
		default:
			assert(false); // we want to know if we forgot to implement new game state
			break;
		}

		state.data = nullptr;
	}

	void HandleWindowEventGameState(Game& game, GameState& state, sf::Event& event)
	{
		switch (state.type)
		{
		case GameStateType::MainMenu:
		{
			HandleGameStateMainMenuWindowEvent(*(GameStateMainMenuData*)state.data, game, event);
			break;
		}
		case GameStateType::Playing:
		{
			HandleGameStatePlayingWindowEvent(*(GameStatePlayingData*)state.data, game, event);
			break;
		}
		case GameStateType::GameOver:
		{
			HandleGameStateGameOverWindowEvent(*(GameStateGameOverData*)state.data, game, event);
			break;
		}
		case GameStateType::ExitDialog:
		{
			HandleGameStateExitDialogWindowEvent(*(GameStateExitDialogData*)state.data, game, event);
			break;
		}
		case GameStateType::Records:
		{
			HandleGameStateRecordsWindowEvent(*(GameStateRecordsData*)state.data, game, event);
			break;
		}
		default:
			assert(false); // we want to know if we forgot to implement new game state
			break;
		}
	}

	void UpdateGameState(Game& game, GameState& state, float timeDelta)
	{
		switch (state.type)
		{
		case GameStateType::MainMenu:
		{
			UpdateGameStateMainMenu(*(GameStateMainMenuData*)state.data, game, timeDelta);
			break;
		}
		case GameStateType::Playing:
		{
			UpdateGameStatePlaying(*(GameStatePlayingData*)state.data, game, timeDelta);
			break;
		}
		case GameStateType::GameOver:
		{
			UpdateGameStateGameOver(*(GameStateGameOverData*)state.data, game, timeDelta);
			break;
		}
		case GameStateType::ExitDialog:
		{
			break;
		}
		case GameStateType::Records:
		{
			UpdateGameStateRecords(*(GameStateRecordsData*)state.data, game, timeDelta);
			break;
		}
		default:
			assert(false); // we want to know if we forgot to implement new game state
			break;
		}
	}

	void DrawGameState(Game& game, GameState& state, sf::RenderWindow& window)
	{
		switch (state.type)
		{
		case GameStateType::MainMenu:
		{
			DrawGameStateMainMenu(*(GameStateMainMenuData*)state.data, game, window);
			break;
		}
		case GameStateType::Playing:
		{
			DrawGameStatePlaying(*(GameStatePlayingData*)state.data, game, window);
			break;
		}
		case GameStateType::GameOver:
		{
			DrawGameStateGameOver(*(GameStateGameOverData*)state.data, game, window);
			break;
		}
		case GameStateType::ExitDialog:
		{
			DrawGameStateExitDialog(*(GameStateExitDialogData*)state.data, game, window);
			break;
		}
		case GameStateType::Records:
		{
			DrawGameStateRecords(*(GameStateRecordsData*)state.data, game, window);
			break;
		}
		default:
			assert(false); // we want to know if we forgot to implement new game state
			break;
		}
	}
}

	


