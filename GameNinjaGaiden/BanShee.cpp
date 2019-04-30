#include "BanShee.h"

void BanShee::onUpdate(float dt)
{
	Camera* camera = Camera::getInstance();
	BANSHEE_ACTION action;

	setAy(GLOBALS_D("weapon_throw_ay"));
	if (player->isDead)
	{
		restoreLocation();
		setAlive(true);
		numberThrow = 1;
		directVx = 1;
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

		if (getRenderActive() && isAlive()) {
			if (weapon_throw->getRenderActive())
			{

				setAnimation(BANSHEE_RUN);
				if (750 < getMidX() && getMidX() < 835)
				{
					if (getMidX() <= 800)
					{
						directVx = 1;
					}
					if (getMidX() >= 820)
					{
						directVx = -1;
					}
					setVx(directVx * GLOBALS_D("enemy_vx"));
				}
				if (1215 < getMidX() && getMidX() < 1250)
				{
					if (getMidX() <= 1220)
					{
						directVx = 1;
					}
					if (getMidX() >= 1239)
					{
						directVx = -1;
					}
					setVx(directVx * 31);
				}
				PhysicsObject::onUpdate(dt);
				return;
			}
			else
			{
				setAnimation(BANSHEE_THROW);
				if (getIsLastFrameAnimationDone())
				{
					switch (numberThrow)
					{
					case 1:
						vxThrow = 15;
						vyThrow = 150;
						break;
					case 2:
						vxThrow = 33;
						vyThrow = 140;
						break;
					case 3:
						vxThrow = 78;
						vyThrow = 180;
						break;
					case 4:
						vxThrow = 93;
						vyThrow = 210;
						numberThrow = 0;
						break;
					}
					numberThrow++;
					weapon_throw->setLocation(getMidX(), getMidY());
					weapon_throw->setVy(vyThrow);
					weapon_throw->setVx(-vxThrow * getDirection());
					weapon_throw->setDirection((TEXTURE_DIRECTION)-getDirection());
					weapon_throw->setRenderActive(true);
					weapon_throw->onUpdate(dt);
				}
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
	setInterval(150);
	player = Player::getInstance();
	weapon_player = WeaponPlayer::getInstance();
	weapon_throw = WeaponThrow::getInstance();
	numberThrow = 1;
	directVx = 1;
}

BanShee::~BanShee()
{
}
