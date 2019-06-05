#include "Gunner.h"

void Gunner::onUpdate(float dt)
{
	Camera* camera = Camera::getInstance();
	GUNNER_ACTION action;

	setFollowPlayer();

	if (player->endDeadTime)
	{
		restoreLocation();
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

		if (getRenderActive() && isAlive())
		{
			if (isShot)
			{
				setAnimation(GUNNER_GUN);
				if (getIsLastFrameAnimationDone())
				{
					numberShot++;
					if (getDirection() == 1)
					{
						weapon_shot->setLocation(getMidX()-13, getMidY()+10);
					}
					else
					{
						weapon_shot->setLocation(getMidX()+13, getMidY()+10);
					}
					
					weapon_shot->setVx(-getDirection() * 45);
					weapon_shot->setDx(-getDirection() * 2);
					weapon_shot->setAnimation(WEAPON_SHOT);
					weapon_shot->setDirection(getDirection());
					weapon_shot->setRenderActive(true);
					weapon_shot->setSprite(SPR(SPRITE_INFO_OTHER_SHOT));
					weapon_shot->onUpdate(dt);
				}
				if (numberShot == 1)
				{
					isShot = false;
					numberShot = 0;
				}
				PhysicsObject::onUpdate(dt);
				return;
			}
			else
			{
				setAnimation(GUNNER_WAIT);

				if (!weapon_shot->getRenderActive())
				{
					isShot = true;
				}
			}
		}
	}
	PhysicsObject::onUpdate(dt);
}

void Gunner::onCollision(MovableRect * other, float collisionTime, int nx, int ny)
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

void Gunner::setFollowPlayer()
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

Gunner::Gunner()
{
	setAnimation(GUNNER_WAIT);
	player = Player::getInstance();
	weapon_player = WeaponPlayer::getInstance();
	weapon_shot = WeaponShot::getInstance();
}

Gunner::~Gunner()
{
}
