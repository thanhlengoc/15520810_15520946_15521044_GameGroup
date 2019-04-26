#include "Butterfly.h"

void Butterfly::onUpdate(float dt)
{
	PhysicsObject::onUpdate(dt);
}

Butterfly::Butterfly()
{
	setPhysicsEnable(false);
	setAnimation(BUTTERFLY_FLY);
	setDirection(TEXTURE_DIRECTION_LEFT);
}

Butterfly::~Butterfly()
{
}
