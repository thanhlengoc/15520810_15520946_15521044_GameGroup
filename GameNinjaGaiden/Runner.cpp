#include "Runner.h"

void Runner::onUpdate(float dt)
{
}

void Runner::onCollision(MovableRect * other, float collisionTime, int nx, int ny)
{
	if (other->getCollisionType() == COLLISION_TYPE_GROUND)
	{
		preventMovementWhenCollision(collisionTime, nx, ny);
	}
}

Runner::Runner()
{
	setAnimation(RUNNER_RUN);
}

Runner::~Runner()
{
}
