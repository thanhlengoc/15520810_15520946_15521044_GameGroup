#include "Butterfly.h"

void Butterfly::onUpdate(float dt)
{

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
	setRenderActive(false);
	setAnimation(BUTTERFLY_FLY);
	setDirection(TEXTURE_DIRECTION_LEFT);
	player = Player::getInstance();
}

Butterfly::~Butterfly()
{
}
