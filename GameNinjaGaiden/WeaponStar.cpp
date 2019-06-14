#include "WeaponStar.h"

WeaponStar* WeaponStar::instance = 0;
WeaponStar* WeaponStar::getInstance()
{
	if (instance == 0)
	{
		instance = new WeaponStar();
	}
	return instance;
}

void WeaponStar::onUpdate(float dt)
{
	setInterval(200);
	if (getRenderActive())
	{
		if (abs(getMidX() - Camera::getInstance()->getMidX()) > 130)
		{
			setVx(0);
			setRenderActive(false);
			PhysicsObject::onUpdate(dt);
			return;
		}
	}
	PhysicsObject::onUpdate(dt);
}

void WeaponStar::onCollision(MovableRect* other, float collisionTime, int nx, int ny)
{
	PhysicsObject::onCollision(other, collisionTime, nx, ny);
}

WeaponStar::WeaponStar()
{
	setSprite(SPR(SPRITE_INFO_WEAPON_STAR));
	setCollisionType(COLLISION_TYPE_STAR);
	setRenderActive(false);
	setPhysicsEnable(false);
}


WeaponStar::~WeaponStar()
{
}
