#pragma once
#include "Entity.h"

class Ship : public Entity
{
public:
	Ship(int maxY);
	~Ship();

	void input(int key);
	void update() override;
	void draw();

	bool Shoot(int frame);

	void takeDamage();

	void AddScore();

	int getHealth() { return health; }
	int getScore() { return score; }

private:

	int health;

	int score;

	int upKey;
	int downKey;

	bool shotQueued;
    int shootKey;
    int shootInterval;
    int lastShotTime;

	int maxY;
};

