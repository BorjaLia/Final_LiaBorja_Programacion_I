#include "GameLoop.h"

#include "AwesomeLibrary.h"

#include "Game.h"
#include "Ship.h"

enum GameState
{
	MENU,
	GAMEPLAY
};

int GameLoop()
{
	bool isRunnig = true;

	bool updateMenuScreen = true;

	GameState gameState = GameState::MENU;

	while (isRunnig)
	{
		switch (gameState)
		{
		case MENU:
		{
			if (updateMenuScreen)
			{
				setForegroundColor(Color::WHITE);
				system("CLS");
				goToCoordinates(getScreenWidth() / 2, getScreenHeight() / 2);
				std::cout << "Ship game!";
				goToCoordinates(getScreenWidth() / 2, (getScreenHeight() / 2) + 1);
				std::cout << "1. Play";
				goToCoordinates(getScreenWidth() / 2, (getScreenHeight() / 2) + 2);
				std::cout << "2. Exit";
				goToCoordinates((getScreenWidth() / 2)-4, (getScreenHeight() - 4));
				setForegroundColor(Color::GRAY);
				std::cout << "Made by Borja Lia";
				setForegroundColor(Color::WHITE);
				updateMenuScreen = false;
			}

			int key = getKey(false);

			if (key == (char)'1')
			{
				gameState = GameState::GAMEPLAY;
			}
			if (key == (char)'2')
			{
				isRunnig = false;
			}

			break;
		}
		case GAMEPLAY:
		{
			Game* currentGame = new Game(mth::Vector2(90, 30));

			Ship ship = Ship(currentGame->gameSpace.y);

			ship.setName("Ship");
			ship.setPos({ 5, 10 });

			std::vector<std::string> shipSprite = {
				std::string({ (char)TileSet::H_LINE, (char)TileSet::H_LINE, (char)TileSet::TR_CORNER, (char)TileSet::EMPTY,(char)TileSet::EMPTY,(char)TileSet::EMPTY,(char)TileSet::EMPTY }),
				std::string({ (char)TileSet::EMPTY, (char)TileSet::EMPTY, (char)TileSet::DOT, (char)TileSet::ARROWS, (char)TileSet::EMPTY,(char)TileSet::EMPTY, (char)TileSet::EMPTY }),
				std::string({ (char)TileSet::EMPTY, (char)TileSet::L_BRACKET, (char)TileSet::V_T_RIGHT, (char)TileSet::R_BRACKET, (char)TileSet::H_LINE, (char)TileSet::H_LINE, (char)TileSet::NOSE }),
				std::string({ (char)TileSet::EMPTY, (char)TileSet::EMPTY, (char)TileSet::DOT, (char)TileSet::ARROWS, (char)TileSet::EMPTY,(char)TileSet::EMPTY, (char)TileSet::EMPTY }),
				std::string({ (char)TileSet::H_LINE, (char)TileSet::H_LINE, (char)TileSet::BR_CORNER, (char)TileSet::EMPTY,(char)TileSet::EMPTY,(char)TileSet::EMPTY,(char)TileSet::EMPTY })
			};

			ship.setSprite(shipSprite);

			ship.setColor(Color::LBLUE);

			currentGame->AddEntity(ship);

			currentGame->play();

			delete currentGame;

			gameState = GameState::MENU;
			updateMenuScreen = true;

			break;
		}
		default:
			break;
		}

	}
	return 0;
}
