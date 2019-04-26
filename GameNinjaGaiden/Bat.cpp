#include "Bat.h"

void Bat::onUpdate(float dt)
{
	PhysicsObject::onUpdate(dt);
}

Bat::Bat()
{
	setPhysicsEnable(false);
	setAnimation(BAT_FLY);
}

Bat::~Bat()
{
}
