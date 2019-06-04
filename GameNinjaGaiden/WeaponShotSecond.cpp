#include "WeaponShotSecond.h"

WeaponShotSecond* WeaponShotSecond::instance = 0;
WeaponShotSecond* WeaponShotSecond::getInstance()
{
	if (instance == 0)
	{
		instance = new WeaponShotSecond();
	}
	return instance;
}

void WeaponShotSecond::onUpdate(float dt)
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
		if (abs(getMidX() - player->getMidX()) < 15 && player->isAttack() && (abs(getMidY() - player->getMidY()) < 10)
			&& getRenderActive())
		{
			bool checkRight = player->getDirection() == 1 && (getMidX() - player->getMidX()) >= 0;
			bool checkLeft = player->getDirection() == -1 && (getMidX() - player->getMidX()) <= 0;
			if (checkRight || checkLeft)
			{
				weapon_player->setRenderActive(true);
				if (getDirection() == 1)
				{
					weapon_player->setLocation(getMidX() + 15, getY() + 15);
				}
				else
				{
					weapon_player->setLocation(getMidX() + 10, getY() + 15);
				}
				weapon_player->startAnimationWeapon();
				weapon_player->setSize(10, 10);

				setVx(0);
				setRenderActive(false);
				PhysicsObject::onUpdate(dt);
				return;
			}
		}
		if (abs(getMidX() - player->getMidX()) <= 2 && abs(getMidY() - player->getMidY()) <= 15 && !player->isHurtLeft && !player->isHurtRight && getRenderActive())
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

void WeaponShotSecond::onCollision(MovableRect* other, float collisionTime, int nx, int ny)
{
	PhysicsObject::onCollision(other, collisionTime, nx, ny);
}

WeaponShotSecond::WeaponShotSecond()
{
	setSprite(SPR(SPRITE_INFO_WEAPON_SHOT));
	setCollisionType(COLLISION_TYPE_WEAPON);
	setRenderActive(false);
	setPhysicsEnable(false);
	weapon_player = WeaponPlayer::getInstance();
}


WeaponShotSecond::~WeaponShotSecond()
{
}
