#include "MachineGun.h"

void Machine::onUpdate(float dt)
{
	PhysicsObject::onUpdate(dt);
}

void Machine::onCollision(MovableRect * other, float collisionTime, int nx, int ny)
{
	if (other->getCollisionType() == COLLISION_TYPE_GROUND)
	{
		preventMovementWhenCollision(collisionTime, nx, ny);
	}
}

Machine::Machine()
{
	setAnimation(MACHINE_GUN_SHOT);
}

Machine::~Machine()
{
}
