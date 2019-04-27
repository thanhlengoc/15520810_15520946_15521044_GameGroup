#include "MachineGun.h"

void Machine::onUpdate(float dt)
{
	Camera* camera = Camera::getInstance();
	MACHINE_GUN_ACTION action;
	setVx(0);

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
		if (isShot)
		{
			setVx(0);
			setAnimation(MACHINE_GUN_SHOT);
			if (getIsLastFrameAnimationDone())
			{
				numberShot++;
			}
			if (numberShot == 2)
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
			setVx(-getDirection() * 30);
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
	PhysicsObject::onUpdate(dt);
}

void Machine::onCollision(MovableRect * other, float collisionTime, int nx, int ny)
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
	setInterval(220);
	player = Player::getInstance();
	isShot = false;
	numberShot = 0;
	numberRun = 0;
}

Machine::~Machine()
{
}
