#include "SwordMan.h"

void SwordMan::onUpdate(float dt)
{
	Camera* camera = Camera::getInstance();
	SWORDMAN_ACTION action;
	setVx(0);

	action = SWORDMAN_ACTION_STAND;

	Weapon* weapon = Weapon::getInstance();

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
		setFollowPlayer();
	}
	else
	{
		setRenderActive(true);
		action = SWORDMAN_ACTION_RUN_ATTACK;
		if (isAlive() && !player->isHurtLeft && !player->isHurtRight)
		{
			if ((abs(getMidX() - player->getMidX()) < 18) && getIsLastFrameAnimationDone() && getRenderActive()
				&& (abs(getBottom() - player->getBottom()) < 10))
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

			if (abs(getMidX() - player->getMidX()) < 36 && player->isAttack() && (abs(getBottom() - player->getBottom()) < 10))
			{
				bool checkRight = player->getDirection() == 1 && (getMidX() - player->getMidX()) >= 0;
				bool checkLeft = player->getDirection() == -1 && (getMidX() - player->getMidX()) <= 0;
				if (checkRight || checkLeft)
				{
					Weapon* weapon = Weapon::getInstance();
					weapon->setRenderActive(true);
					if (getDirection() == 1)
					{
						weapon->set(getX() + 10, getY(), getWidth(), getHeight());
					}
					else
					{
						weapon->set(getX(), getY(), getWidth(), getHeight());
					}

					restoreLocation();
					setRenderActive(false);
					setAlive(false);
					PhysicsObject::onUpdate(dt);
					return;
				}
			}
		}

		if (0 < getMidX() && getMidX() < 600)
		{
			if (getX() <= 40)
			{
				setDirection(TEXTURE_DIRECTION_LEFT);
			}
			if (getX() >= 510)
			{
				setDirection(TEXTURE_DIRECTION_RIGHT);
			}
		}
		else if(1100 < getMidX() && getMidX() < 1400){
			if (getX() <= 1288)
			{
				setDirection(TEXTURE_DIRECTION_LEFT);
			}
			if (getX() >= 1351)
			{
				setDirection(TEXTURE_DIRECTION_RIGHT);
			}
		}
		else if (1445 < getMidX() && getMidX() < 1472)
		{
			if (getX() <= 1436)
			{
				setDirection(TEXTURE_DIRECTION_LEFT);
			}
			if (getX() >= 1447)
			{
				setDirection(TEXTURE_DIRECTION_RIGHT);
			}
			setVx(-getDirection() * 31.2);
			setAnimation(action);
			PhysicsObject::onUpdate(dt);
			return;
		}
		else if (1473 < getMidX() && getMidX() < 1535)
		{
			if (getX() <= 1470)
			{
				setDirection(TEXTURE_DIRECTION_LEFT);
			}
			if (getX() >= 1519)
			{
				setDirection(TEXTURE_DIRECTION_RIGHT);
			}
		}
		else if (1700 < getMidX() && getMidX() < 2100)
		{
			if (getX() <= 1807)
			{
				setDirection(TEXTURE_DIRECTION_LEFT);
			}
			if (getX() >= 2020)
			{
				setDirection(TEXTURE_DIRECTION_RIGHT);
			}
		}
		setVx(-getDirection() * 32);
	}

	setAnimation(action);
	PhysicsObject::onUpdate(dt);
}

void SwordMan::onCollision(MovableRect * other, float collisionTime, int nx, int ny)
{
	if (other->getCollisionType() == COLLISION_TYPE_GROUND)
	{
		preventMovementWhenCollision(collisionTime, nx, ny);
	}
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

	PhysicsObject::onCollision(other, collisionTime, nx, ny);
}

void SwordMan::setFollowPlayer()
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

SwordMan::SwordMan()
{
	setAnimation(SWORDMAN_ACTION_STAND);
	setInterval(200);
	player = Player::getInstance();
}

SwordMan::~SwordMan()
{
}
