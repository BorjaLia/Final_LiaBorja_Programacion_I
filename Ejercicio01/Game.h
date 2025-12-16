#pragma once

#include <vector>

#include "Math.h"
#include "Utils.h"

#include "Entity.h"

#include "HUD.h"

class Game
{
public:
	Game(mth::Vector2 size);
	~Game();

	int play();

	void AddEntity(Entity& entity);

	mth::Vector2 gameSpace;
private:
	std::vector<Entity*> entities;

	int frame;

	int lastInput;

	int winScore;

	int activeAsteroids;
	int asteroidLimit;
	int asteroidInterval;
	int asteroidLastSpawn;

	HUD* Hud;

	void init();

	void input();
	void update(bool& isRunning);
	void draw(bool isRunning);

	void asteroidSpawner();
};

