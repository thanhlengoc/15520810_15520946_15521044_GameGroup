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
		if (abs(getMidX() - player->getMidX()) <= 10 && abs(getMidY() - player->getMidY()) <= 10 && !player->isHurtLeft && !player->isHurtRight && getRenderActive())
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
	weapon_player = WeaponPlayer::getInstance();
}


WeaponThrow::~WeaponThrow()
{
}
