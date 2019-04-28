#include "BanShee.h"

void BanShee::onUpdate(float dt)
{
	Camera* camera = Camera::getInstance();
	BANSHEE_ACTION action;
	setVx(0);

	if (player->isDead)
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
		setFollowPlayer();
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
					weapon_player->set(getX() + 10, getY(), getWidth(), getHeight());
				}
				else
				{
					weapon_player->set(getX(), getY(), getWidth(), getHeight());
				}

				restoreLocation();
				weapon_throw->setRenderActive(false);
				setRenderActive(false);
				setAlive(false);
				PhysicsObject::onUpdate(dt);
				return;
			}
		}

		if (810 < getMidX() && getMidX() < 840)
		{
			if (getX() <= 800)
			{
				setVx(31);
			}
			if (getX() >= 835)
			{
				setVx(-31);
			}
		}
		else if (1216 < getMidX() && getMidX() < 1247)
		{
			if (getX() <= 1211)
			{
				setVx(31);
			}
			if (getX() >= 1242)
			{
				setVx(-31);
			}
		}
		if (getRenderActive() && isAlive())
		{
			if (!weapon_throw->getRenderActive())
			{
				setAnimation(BANSHEE_THROW);
				if (getIsLastFrameAnimationDone())
				{
					switch (numberThrow)
					{
					case 1:
						vxThrow = 33;
						vyThrow = 140;
						break;
					case 2:
						vxThrow = 78;
						vyThrow = 180;
						break;
					case 3:
						vxThrow = 93;
						vyThrow = 210;
						numberThrow = 0;
						break;
					}
					numberThrow++;
					weapon_throw->setLocation(getMidX(), getMidY());
					weapon_throw->setVy(vyThrow);
					weapon_throw->setVx(-vxThrow*getDirection());
					weapon_throw->setDirection((TEXTURE_DIRECTION)-getDirection());
					weapon_throw->setRenderActive(true);
					weapon_throw->onUpdate(dt);

				}
				PhysicsObject::onUpdate(dt);
			}
			else
			{
				setAnimation(BANSHEE_RUN);
			}
		}
	}
	PhysicsObject::onUpdate(dt);
}

void BanShee::onCollision(MovableRect * other, float collisionTime, int nx, int ny)
{
	if (other->getCollisionType() == COLLISION_TYPE_PLAYER && getRenderActive() && isAlive())
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

void BanShee::setFollowPlayer()
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

BanShee::BanShee()
{
	setAnimation(BANSHEE_WAIT);
	setInterval(200);
	player = Player::getInstance();
	weapon_player = WeaponPlayer::getInstance();
	weapon_throw = WeaponThrow::getInstance();
	numberThrow = 1;
}

BanShee::~BanShee()
{
}
