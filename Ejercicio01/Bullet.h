#pragma once
#include "Entity.h"
class Bullet : public Entity
{
public:
	Bullet(mth::Vector2 pos, mth::Vector2 dir, Color color, const std::vector<std::string>& sprite,int maxDistance);
	~Bullet();

	void update() override;
	void draw();

private:

	int maxDistance;

};

