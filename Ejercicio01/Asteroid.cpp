#include "Asteroid.h"
#include "Utils.h"


Asteroid::Asteroid(mth::Vector2 pos, mth::Vector2 dir, Color color, const std::vector<std::string>& sprite, int minDistance) : Entity::Entity()
{
	setPos(pos);
	setDir(dir);
	setColor(color);
	setSprite(sprite);

	this->minDistance = minDistance;
}

Asteroid::~Asteroid()
{
}

void Asteroid::update()
{
	if (this->getPos().x <= minDistance)
	{
		this->setToRemove();
	}
	else
	{
		Entity::update();
	}
}

void Asteroid::draw()
{
	setForegroundColor(this->getColor());

	mth::Vector2 currentDir = getDir();

	mth::Vector2 currentPos = getPos();

	for (int i = 0; i < getSize().y; i++)
	{
		GoTo(currentPos.x - currentDir.x, currentPos.y + i - currentDir.y);

		for (int j = 0; j < getSize().x; j++)
		{
			std::cout << ' ';
		}
	}

	if (shouldRemove())
	{
		for (int i = 0; i < getSize().y; i++)
		{
			currentPos = getPos();
			GoTo(currentPos.x, currentPos.y + i);

			for (int j = 0; j < getSize().x; j++)
			{
				std::cout << ' ';
			}
		}
		setForegroundColor(Color::WHITE);
		return;
	}

	for (int i = 0; i < getSize().y; i++)
	{
		currentPos = getPos();
		GoTo(currentPos.x, currentPos.y + i);

		std::cout << getSprite(i);
	}
	setForegroundColor(Color::WHITE);
}