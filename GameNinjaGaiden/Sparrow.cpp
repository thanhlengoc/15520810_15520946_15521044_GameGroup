#include "Sparrow.h"

void Sparrow::onUpdate(float dt)
{
}

void Sparrow::onCollision(MovableRect * other, float collisionTime, int nx, int ny)
{
}

void Sparrow::setFollowPlayer()
{
	int distance = player->getMidX() - getMidX();
	if (distance < 0)
	{
		setDirection(TEXTURE_DIRECTION_RIGHT);
	}
	else
	{
		setDirection(TEXTURE_DIRECTION_LEFT);
	}
}

Sparrow::Sparrow()
{
	setPhysicsEnable(false);
	setAnimation(SPARROW_FLY);
	player = Player::getInstance();
}

Sparrow::~Sparrow()
{
}
