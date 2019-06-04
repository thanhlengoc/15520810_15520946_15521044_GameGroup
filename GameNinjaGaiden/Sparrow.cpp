#include "Sparrow.h"

void Sparrow::onUpdate(float dt)
{
	setFollowPlayer();
	if (player->endDeadTime)
	{
		restoreLocation();
		setRenderActive(true);
		PhysicsObject::onUpdate(dt);
		return;
	}
	if (abs(getMidX() - player->getMidX()) < 10 && player->isAttack() && abs(getMidY() - player->getMidY()) < 10)
	{
		setRenderActive(false);
	}
	PhysicsObject::onUpdate(dt);
}

void Sparrow::setFollowPlayer()
{
	int distance = player->getMidX() - getMidX();
	if (distance < 0)
	{
		setDirection(TEXTURE_DIRECTION_LEFT);
	}
	else
	{
		setDirection(TEXTURE_DIRECTION_RIGHT);
	}
}

Sparrow::Sparrow()
{
	setPhysicsEnable(false);
	setAnimation(SPARROW_FLY);
	setDirection(TEXTURE_DIRECTION_LEFT);
	player = Player::getInstance();
}

Sparrow::~Sparrow()
{
}
