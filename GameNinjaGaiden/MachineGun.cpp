#include "MachineGun.h"

void Machine::onUpdate(float dt)
{
	Camera* camera = Camera::getInstance();
	MACHINE_GUN_ACTION action;
	setVx(0);

	if (player->endDeadTime)
	{
		restoreLocation();
		setVx(0);
		PhysicsObject::onUpdate(dt);
		return;
	}

	if (abs(getMidX() - camera->getMidX()) > 110)
	{
		setAlive(true);
		setRenderActive(false);
	}
	else
	{
		setRenderActive(true);
		if (abs(getMidX() - player->getMidX()) < 36 && player->isAttack()
			&& (abs(getBottom() - player->getBottom()) < 10) && isAlive())
		{
			bool checkRight = player->getDirection() == 1 && (getMidX() - player->getMidX()) >= 0;
			bool checkLeft = player->getDirection() == -1 && (getMidX() - player->getMidX()) <= 0;
			if (checkRight || checkLeft)
			{
				weapon_player->setRenderActive(true);
				if (getDirection() == 1)
				{
					weapon_player->setLocation(getMidX() + 15, getY());
				}
				else
				{
					weapon_player->setLocation(getMidX() + 10, getY());
				}
				weapon_player->startAnimationWeapon();

				restoreLocation();
				setRenderActive(false);
				setAlive(false);
				PhysicsObject::onUpdate(dt);
				return;
			}
		}

		if (player->isDead || player->getFreezeTime())
		{
			setPauseAnimation(true);
			setVx(0);
			setVy(0);
			PhysicsObject::onUpdate(dt);
			return;
		}
		else
			setPauseAnimation(false);

		if (1129 < getMidX() && getMidX() < 1403)
		{
			if (getX() <= 1140)
			{
				setDirection(TEXTURE_DIRECTION_LEFT);
			}
			if (getX() >= 1395)
			{
				setDirection(TEXTURE_DIRECTION_RIGHT);
			}
		}
		if (getRenderActive() && isAlive())
		{
			if (isShot)
			{
				setVx(0);
				setAnimation(MACHINE_GUN_SHOT);
				if (getIsLastFrameAnimationDone())
				{
					numberShot++;
					switch (numberShot)
					{
					case 1:
						weapon_shot->setLocation(getMidX(), getMidY());
						weapon_shot->setVx(-getDirection() * 32);
						weapon_shot->setDx(-getDirection() * 2);
						weapon_shot->setAnimation(WEAPON_SHOT);
						weapon_shot->setDirection(getDirection());
						weapon_shot->setRenderActive(true);
						weapon_shot->setSprite(SPR(SPRITE_INFO_WEAPON_SHOT));
						weapon_shot->onUpdate(dt);
						break;
					case 2:
						weapon_shot_second->setLocation(getMidX(), getMidY());
						weapon_shot_second->setVx(-getDirection() * 32);
						weapon_shot_second->setDx(-getDirection() * 2);
						weapon_shot_second->setAnimation(WEAPON_SHOT);
						weapon_shot_second->setDirection(getDirection());
						weapon_shot_second->setRenderActive(true);
						weapon_shot->setSprite(SPR(SPRITE_INFO_WEAPON_SHOT));
						weapon_shot_second->onUpdate(dt);
						break;
					case 3:
						weapon_shot_three->setLocation(getMidX(), getMidY());
						weapon_shot_three->setVx(-getDirection() * 32);
						weapon_shot_three->setDx(-getDirection() * 2);
						weapon_shot_three->setAnimation(WEAPON_SHOT);
						weapon_shot_three->setDirection(getDirection());
						weapon_shot_three->setRenderActive(true);
						weapon_shot->setSprite(SPR(SPRITE_INFO_WEAPON_SHOT));
						weapon_shot_three->onUpdate(dt);
					default:
						break;
					}
					
				}
				if (numberShot == 3)
				{
					isShot = false;
					numberShot = 0;
				}
				PhysicsObject::onUpdate(dt);
				return;
			}
			else
			{
				setFollowPlayer();
				setVx(-getDirection() * 31.2);
				setAnimation(MACHINE_GUN_RUN);
				if (getIsLastFrameAnimationDone())
				{
					numberRun++;
				}
				if (numberRun == 3)
				{
					isShot = true;
					numberRun = 0;
				}
			}
		}
	}
	PhysicsObject::onUpdate(dt);
}

void Machine::onCollision(MovableRect * other, float collisionTime, int nx, int ny)
{
	if (other->getCollisionType() == COLLISION_TYPE_PLAYER && getRenderActive() && isAlive()
		&& !player->isDead && !player->isHurtLeft && !player->isHurtRight)
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
	if (other->getCollisionType() == COLLISION_TYPE_GROUND)
	{
		preventMovementWhenCollision(collisionTime, nx, ny);
	}
	PhysicsObject::onCollision(other, collisionTime, nx, ny);
}

void Machine::setFollowPlayer()
{
	int distance = player->getMidX() - getMidX();
	if (distance < 0)
	{
		setDirection(TEXTURE_DIRECTION_RIGHT);
	}
	else
	{
		setDirection(TEXTURE_DIRECTION_LEFT);
	}
}

Machine::Machine()
{
	setAnimation(MACHINE_GUN_WAIT);
	setInterval(150);
	player = Player::getInstance();
	weapon_player = WeaponPlayer::getInstance();
	weapon_shot = WeaponShot::getInstance();
	weapon_shot_second = WeaponShotSecond::getInstance();
	weapon_shot_three = WeaponShotThree::getInstance();
	numberShot = 0;
	numberRun = 0;
}

Machine::~Machine()
{
}
