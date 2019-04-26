#include "Bird.h"

void Bird::onUpdate(float dt)
{
	PhysicsObject::onUpdate(dt);
}

Bird::Bird()
{
	setPhysicsEnable(false);
	setAnimation(BIRD_FLY);
}

Bird::~Bird()
{
}
