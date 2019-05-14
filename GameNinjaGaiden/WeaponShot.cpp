#include "WeaponShot.h"

WeaponShot * WeaponShot::instance = 0;
WeaponShot * WeaponShot::getInstance()
{
	if (instance == 0)
	{
		instance = new WeaponShot();
	}
	return instance;
}

void WeaponShot::onUpdate(float dt)
{
	Player* player = Player::getInstance();
	setInterval(200);
	if (getRenderActive())
	{
		if (abs(getMidX() - Camera::getInstance()->getMidX()) > 110)
		{
			setVx(0);
			setRenderActive(false);
			PhysicsObject::onUpdate(dt);
			return;
		}
		if (abs(getMidX() - player->getMidX()) <= 2 && abs(getMidY() - player->getMidY()) <= 15 && !player->isHurtLeft && !player->isHurtRight)
		{
			if ((getMidX() - player->getMidX()) > 0)
			{
				player->isHurtRight = true;
			}
			else
			{
				player->isHurtLeft = true;
			}
		}
	}
	PhysicsObject::onUpdate(dt);
}

void WeaponShot::onCollision(MovableRect * other, float collisionTime, int nx, int ny)
{
	PhysicsObject::onCollision(other, collisionTime, nx, ny);
}

WeaponShot::WeaponShot()
{
	setSprite(SPR(SPRITE_INFO_WEAPON_SHOT));
	setCollisionType(COLLISION_TYPE_WEAPON);
	setRenderActive(false);
	setPhysicsEnable(false);
}


WeaponShot::~WeaponShot()
{
}
