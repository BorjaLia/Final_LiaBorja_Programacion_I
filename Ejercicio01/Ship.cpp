#include "Ship.h"
#include "Utils.h"

Ship::Ship(int maxY)
{
	health = 3;

	score = 0;

	upKey = KEY_UP;
	downKey = KEY_DOWN;

	shotQueued = false;
	shootKey = KEY_RIGHT;
	shootInterval = 15;
	lastShotTime = 0;

	this->maxY = maxY;
}

Ship::~Ship()
{
}

void Ship::input(int key)
{
	if (key == upKey)
	{
		setDir({ 0,-1 });
	}
	else if (key == downKey)
	{
		setDir({ 0,1 });
	}
	else
	{
		setDir({ 0,0 });
	}

	if (key == shootKey)
	{
		shotQueued = true;
	}
}

void Ship::update()
{
	Entity::update();

	mth::Vector2 pos = getPos();
	mth::Vector2 size = getSize();

	if (pos.y < 1)
	{
		setPos({ pos.x,pos.y + 1 });
	}

	if (pos.y + size.y >= maxY)
	{
		setPos({ pos.x,pos.y - 1 });
	}
}

void Ship::draw()
{
	setForegroundColor(this->getColor());

	mth::Vector2 currentDir = getDir();

	if ((currentDir.x == 0 && currentDir.y == 0) && lastShotTime > time(0))
	{
		return;
	}

	mth::Vector2 currentPos = getPos();

	for (int i = 0; i < getSize().y; i++)
	{
		GoTo(currentPos.x - currentDir.x, currentPos.y + i - currentDir.y);

		for (int j = 0; j < getSize().x; j++)
		{
			std::cout << ' ';
		}
	}

	for (int i = 0; i < getSize().y; i++)
	{
		currentPos = getPos();
		GoTo(currentPos.x, currentPos.y + i);

		std::cout << getSprite(i);
	}
	setForegroundColor(Color::WHITE);
}

bool Ship::Shoot(int frame)
{
	int currentTime = frame;
	if (shotQueued && currentTime > lastShotTime + shootInterval)
	{
		lastShotTime = currentTime;
		shotQueued = false;
		return true;
	}
	return false;
}

void Ship::takeDamage()
{
	health--;
}

void Ship::AddScore()
{
	score++;
}
