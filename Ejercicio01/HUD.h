#pragma once

#include "Ship.h"

class HUD
{
public:
	HUD(Ship* ship,mth::Vector2 pos);
	~HUD();

	void DrawHUD(int maxScore);

	void DrawVictory();
	void DrawDefeat();

	void AddAsteroid();
	void RemoveAsteroid();

private:

	mth::Vector2 pos;
	Ship* ship;

};

