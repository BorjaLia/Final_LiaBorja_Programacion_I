#pragma once
#include "Entity.h"
class Asteroid : public Entity
{
public:
	Asteroid(mth::Vector2 pos, mth::Vector2 dir, Color color, const std::vector<std::string>& sprite, int minDistance);
	~Asteroid();

	void update() override;
	void draw();

private:

	int minDistance;
};


