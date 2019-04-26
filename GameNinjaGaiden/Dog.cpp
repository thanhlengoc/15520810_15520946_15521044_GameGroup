#include "Dog.h"

void Dog::onUpdate(float dt)
{
	PhysicsObject::onUpdate(dt);
}

void Dog::onCollision(MovableRect * other, float collisionTime, int nx, int ny)
{
	if (other->getCollisionType() == COLLISION_TYPE_GROUND)
		preventMovementWhenCollision(collisionTime, nx, ny);
}

Dog::Dog()
{
	setAnimation(DOG_RUN);
}

Dog::~Dog()
{
}
