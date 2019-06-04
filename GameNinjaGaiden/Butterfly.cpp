#include "Butterfly.h"

void Butterfly::setFollowPlayer()
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

void Butterfly::onUpdate(float dt)
{
	setFollowPlayer();
	if (player->endDeadTime)
	{
		restoreLocation();
		setRenderActive(true);
		PhysicsObject::onUpdate(dt);
		return;
	}
	if ( abs(getMidX() - player->getMidX()) < 10 && player->isAttack() && abs(getMidY() - player->getMidY()) < 10)
	{
		setRenderActive(false);
	}
	PhysicsObject::onUpdate(dt);
}

Butterfly::Butterfly()
{
	setPhysicsEnable(false);
	setAnimation(BUTTERFLY_FLY);
	setDirection(TEXTURE_DIRECTION_LEFT);
	player = Player::getInstance();
}

Butterfly::~Butterfly()
{
}
