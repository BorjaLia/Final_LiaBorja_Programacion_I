#pragma once

#include "AwesomeLibrary.h"
#include "Math.h"
#include <iostream>
#include <vector>

enum TileSet : unsigned char
{
	EMPTY = 32,
	L_BRACKET = 91,
	R_BRACKET = 93,
	H_LINE = 205,
	TR_CORNER = 187,
	BR_CORNER = 188,
	V_T_RIGHT = 204,
	DOT = 231,
	ARROWS = 175,
	NOSE = 62
};

class Entity
{
public:
	Entity();
	Entity(const std::vector<std::string>& newSprite);
	~Entity();

	void setName(std::string name);
	void setPos(mth::Vector2 pos);
	void setSize(mth::Vector2 size);
	void setDir(mth::Vector2 dir);
	void setColor(Color color);
	
	void setSprite(const std::vector<std::string>& newSprite);

	const inline std::string getname() { return name; }
	const inline mth::Vector2 getPos() { return pos; }
	const inline mth::Vector2 getSize() { return size; }
	const inline mth::Vector2 getDir() { return dir; }
	const inline Color getColor() { return color; }
	
	const std::vector<std::string>& getSpriteVector() const { return sprite; }
	const std::string& getSprite(int index = 0) const { return sprite[index]; }

	bool shouldRemove() { return remove; }

	void setToRemove();

	virtual void update();
	virtual void draw() = 0;

	bool collision(Entity* entity);

private:

	bool remove;
	
	int id;

	std::string name;

	mth::Vector2 pos;
	mth::Vector2 size;

	mth::Vector2 dir;

	Color color;

	std::vector<std::string> sprite;
};

