#include "Game.h"

#include "AwesomeLibrary.h"
#include "Ship.h"
#include "Bullet.h"
#include "Asteroid.h"

Game::Game(mth::Vector2 size)
{
	gameSpace = size;
	entities.clear();

	frame = 0;

	lastInput = 0;

	winScore = 15;

	activeAsteroids = 0;
	asteroidLimit = 7;
	asteroidInterval = 30;
	asteroidLastSpawn = 0;
}

Game::~Game()
{
	if (Hud)
	{
		delete Hud;
	}
}

int Game::play()
{
	bool isRunning = true;

	init();
	draw(isRunning);

	while (isRunning)
	{
		frame++;
		input();
		update(isRunning);
		draw(isRunning);

		miliSleep((1.0f / 60.0f) * 100);
	}
	while (getKey() != KEY_ESC);
	return 0;
}

void Game::AddEntity(Entity& entity)
{
	entities.push_back(&entity);
}

void Game::init()
{
	srand(time(nullptr));

	Hud = new HUD(static_cast<Ship*>(entities[0]), mth::Vector2(gameSpace.x + 3,gameSpace.y/3));

	system("CLS");

	setTitle("Final - Borja Lia - Programacion I");
	hideCursor();

	drawFrame(1, 1, gameSpace.x, gameSpace.y);
}

void Game::input()
{
	lastInput = getKey(false);

	//0 is always ship
	Ship* ship = static_cast<Ship*>(entities[0]);

	ship->input(lastInput);
}

void Game::update(bool& isRunning)
{
	Ship* ship = static_cast<Ship*>(entities[0]);

	if (getKey(false) == KEY_ESC || ship->getHealth() <= 0 || ship->getScore() >= winScore)
	{
		isRunning = false;
		return;
	}


	asteroidSpawner();

	for (int i = entities.size() - 1; i >= 0; i--)
	{
		if (entities[i]->shouldRemove())
		{
			if (dynamic_cast<Asteroid*>(entities[i]))
			{
				Hud->RemoveAsteroid();
				activeAsteroids--;
			}

			delete entities[i];
			entities.erase(entities.begin() + i);
		}
	}

	for (int i = 0; i < entities.size(); i++)
	{
		for (int j = i + 1; j < entities.size(); j++)
		{
			if (entities[i]->collision(entities[j]))
			{
				//ship
				if (i == 0 && dynamic_cast<Asteroid*>(entities[j]) != nullptr)
				{
					entities[j]->setToRemove();
					ship->takeDamage();
					goToCoordinates(entities[j]->getPos().x, entities[j]->getPos().y+1);
					setForegroundColor(Color::RED);
					std::cout << "!!";
					setForegroundColor(Color::WHITE);
					miliSleep(250);
					goToCoordinates(entities[j]->getPos().x, entities[j]->getPos().y+1);
					std::cout << "  ";
				}

				if (i != 0)
				{
					entities[i]->setToRemove();
					entities[j]->setToRemove();

					ship->AddScore();

					goToCoordinates(entities[j]->getPos().x, entities[j]->getPos().y+1);
					setForegroundColor(Color::RED);
					std::cout << "!!";
					setForegroundColor(Color::WHITE);
					miliSleep(100);
					goToCoordinates(entities[j]->getPos().x, entities[j]->getPos().y+1);
					std::cout << "  ";
				}
			}
		}
	}

	for (int i = 0; i < entities.size(); i++)
	{
		entities[i]->update();
	}

	if (ship->Shoot(frame))
	{
		std::vector<std::string> bulletSprite = {
		std::string({ (char)TileSet::H_LINE, (char)TileSet::H_LINE })
		};
		Bullet* bullet = new Bullet(mth::Vector2(ship->getPos().x + 3, ship->getPos().y + 3), mth::Vector2(1, 0), Color::YELLOW, bulletSprite, gameSpace.x - 2);
		entities.push_back(bullet);
		Bullet* bullet2 = new Bullet(mth::Vector2(ship->getPos().x + 3, ship->getPos().y + 1), mth::Vector2(1, 0), Color::YELLOW, bulletSprite, gameSpace.x - 2);
		entities.push_back(bullet2);
	}
}

void Game::draw(bool isRunning)
{
	for (int i = 0; i < entities.size(); i++)
	{
		entities[i]->draw();
	}
	Ship* ship = static_cast<Ship*>(entities[0]);
	Hud->DrawHUD();

	if (!isRunning)
	{
		if (ship->getScore() >= winScore)
		{
			Hud->DrawVictory();
		}
		else
		{
			Hud->DrawDefeat();
		}
	}
}

void Game::asteroidSpawner()
{
	if (activeAsteroids < asteroidLimit && asteroidLastSpawn + asteroidInterval < frame)
	{
		asteroidLastSpawn = frame;
		activeAsteroids++;
		Hud->AddAsteroid();

		std::vector<std::string> asteroidSprite = {
		std::string({'*'})
		};

		Asteroid* asteroid = new Asteroid(mth::Vector2(gameSpace.x - 2, (rand() % (int)(gameSpace.y - 2)) + 1), mth::Vector2(-0.5f, 0), Color::BROWN, asteroidSprite, 1);
		entities.push_back(asteroid);
	}
}
