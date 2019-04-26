#include "BanShee.h"

void BanShee::onUpdate(float dt)
{
	PhysicsObject::onUpdate(dt);
}

void BanShee::onCollision(MovableRect * other, float collisionTime, int nx, int ny)
{
	if (other->getCollisionType() == COLLISION_TYPE_GROUND)
	{
		preventMovementWhenCollision(collisionTime, nx, ny);
	}
}

BanShee::BanShee()
{
	setAnimation(BANSHEE_THROW);
}

BanShee::~BanShee()
{
}
