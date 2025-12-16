#include "Entity.h"

void Entity::setName(std::string name) { this->name = name; }
void Entity::setPos(mth::Vector2 pos) { this->pos = pos; }
void Entity::setSize(mth::Vector2 size) { this->size = size; }
void Entity::setDir(mth::Vector2 dir) { this->dir = dir; }
void Entity::setColor(Color color) { this->color = color; }

Entity::Entity()
{
	remove = false;

	id = -1;

	name = "No Name";

	pos = { 0,0 };
	size = { 0,0 };

	dir = { 1,1 };

	color = Color::WHITE;
}

inline Entity::Entity(const std::vector<std::string>& newSprite) : Entity::Entity()
{
	setSprite(newSprite);
}

Entity::~Entity()
{
	//std::cout << "Entity " << name << "deleted";
}

void Entity::setSprite(const std::vector<std::string>& newSprite)
{
	sprite = newSprite;

	if (!sprite.empty())
	{
		size.y = sprite.size();
		size.x = sprite[0].size();
	}
}

void Entity::setToRemove()
{
	remove = true;
}

void Entity::update()
{
	pos.x += dir.x;
	pos.y += dir.y;
}

bool Entity::collision(Entity* entity)
{
	if ((int)pos.x >= (int)entity->getPos().x + (int)std::abs(entity->getDir().x) + (int)entity->getSize().x || (int)pos.x + (int)size.x + (int)std::abs(dir.x)<= (int)entity->getPos().x)
	{
		return false;
	}

	if ((int)pos.y >= (int)entity->getPos().y + (int)entity->getSize().y || (int)pos.y + (int)size.y <= (int)entity->getPos().y)
	{
		return false;
	}

	return true;
}
