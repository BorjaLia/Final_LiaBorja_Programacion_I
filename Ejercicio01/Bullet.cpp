#include "Bullet.h"
#include "Utils.h"

Bullet::Bullet(mth::Vector2 pos, mth::Vector2 dir, Color color, const std::vector<std::string>& sprite, int maxDistance) : Entity::Entity()
{
	setPos(pos);
	setDir(dir);
	setColor(color);
	setSprite(sprite);

	this->maxDistance = maxDistance;
}

Bullet::~Bullet()
{
}

void Bullet::update()
{
	if (this->getPos().x + this->getSize().x > maxDistance)
	{
		this->setToRemove();
	}
	else
	{
		Entity::update();
	}
}

void Bullet::draw()
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