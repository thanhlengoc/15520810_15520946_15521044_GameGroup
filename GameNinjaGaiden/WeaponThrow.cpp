#include "WeaponThrow.h"

WeaponThrow * WeaponThrow::instance = 0;
WeaponThrow * WeaponThrow::getInstance()
{
	if (instance == 0)
	{
		instance = new WeaponThrow();
	}
	return instance;
}

void WeaponThrow::onUpdate(float dt)
{
	Player* player = Player::getInstance();
	setInterval(200);
	if (getRenderActive())
	{
		setAnimation(WEAPON_THROW);
		if (Camera::getInstance()->getBottom() - getBottom()>0)
		{
			setVx(0);
			setRenderActive(false);
			PhysicsObject::onUpdate(dt);
			return;
		}
		if (abs(getMidX() - player->getMidX()) <= 10 && abs(getMidY() - player->getMidY()) <= 10 && !player->isHurtLeft && !player->isHurtRight)
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

void WeaponThrow::onCollision(MovableRect * other, float collisionTime, int nx, int ny)
{
	PhysicsObject::onCollision(other, collisionTime, nx, ny);
}

WeaponThrow::WeaponThrow()
{
	setSprite(SPR(SPRITE_INFO_WEAPON_THROW));
	setCollisionType(COLLISION_TYPE_WEAPON);
	setRenderActive(false);
}


WeaponThrow::~WeaponThrow()
{
}
