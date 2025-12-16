#include "HUD.h"

static int asteroidAmount = 0;

HUD::HUD(Ship* ship, mth::Vector2 pos)
{
	this->pos = pos;
	this->ship = ship;
}

HUD::~HUD()
{
}

void HUD::DrawHUD()
{
	goToCoordinates(pos.x, pos.y);
	std::cout << "Asteroids: " << asteroidAmount;
	goToCoordinates(pos.x, pos.y + 1);
	std::cout << "Lives: ";
	for (int i = 0; i < 3; i++)
	{
		if (ship->getHealth() > i)
		{
			std::cout << "<3 ";
		}
		else
		{
			std::cout << "   ";
		}
	}
	goToCoordinates(pos.x, pos.y + 2);
	std::cout << "Score: " << ship->getScore();
}

void HUD::DrawVictory()
{
	system("CLS");
	goToCoordinates(getScreenWidth()/2,getScreenHeight()/2);
	std::cout << "you've won!";
	goToCoordinates((getScreenWidth() / 2)-2, (getScreenHeight() / 2) + 1);
	setForegroundColor(Color::GRAY);
	std::cout << "Esc to go to menu";
	setForegroundColor(Color::WHITE);
}

void HUD::DrawDefeat()
{
	system("CLS");
	goToCoordinates(getScreenWidth()/2,getScreenHeight()/2);
	std::cout << "you've lost!";
	goToCoordinates((getScreenWidth() / 2)-2, (getScreenHeight() / 2) + 1);
	setForegroundColor(Color::GRAY);
	std::cout << "Esc to go to menu";
	setForegroundColor(Color::WHITE);
}

void HUD::AddAsteroid()
{
	asteroidAmount++;
}

void HUD::RemoveAsteroid()
{
	asteroidAmount--;
}
