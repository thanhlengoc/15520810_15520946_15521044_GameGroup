#include "Dog.h"

void Dog::onUpdate(float dt)
{
	Camera* camera = Camera::getInstance();
	DOG_ACTION action;

	action = DOG_WAIT;

	Weapon* weapon = Weapon::getInstance();

	if (player->isDead)
	{
		restoreLocation();
		setRenderActive(false);
		setAlive(false);
		PhysicsObject::onUpdate(dt);
		return;
	}
	if (!isAlive())
	{
		setDirectDefault();
	}
	float distanceVisible = getMidX() - camera->getMidX();
	if (getDirection()==1)
	{
		if (108<=distanceVisible && distanceVisible<=110 && !isAlive())
		{
			setRenderActive(true);
			setAlive(true);
		}
	}
	else
	{
		if (-110 <= distanceVisible && distanceVisible <= -108 && isAlive())
		{
			setRenderActive(true);
			setAlive(true);
		}
	}
	if (isAlive())
	{
		if (abs(getMidX() - camera->getMidX()) >= 125)
		{
			restoreLocation();
			setRenderActive(false);
			setAlive(false);
			PhysicsObject::onUpdate(dt);
			return;
		}
	}
	if ((abs(getMidX() - player->getMidX()) < 18) && getRenderActive()
		&& (abs(getBottom() - player->getBottom()) < 10) && !player->isHurtLeft && !player->isHurtRight)
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

	if (abs(getMidX() - player->getMidX()) < 36 && player->isAttack() && (abs(getBottom() - player->getBottom()) < 10)
		&&getRenderActive())
	{
		bool checkRight = player->getDirection() == 1 && (getMidX() - player->getMidX()) >= 0;
		bool checkLeft = player->getDirection() == -1 && (getMidX() - player->getMidX()) <= 0;
		if (checkRight || checkLeft)
		{
			Weapon* weapon = Weapon::getInstance();
			weapon->setRenderActive(true);
			if (getDirection() == 1)
			{
				weapon->set(getX() + 10, getY()+30, getWidth(), getHeight());
			}
			else
			{
				weapon->set(getX(), getY()+30, getWidth(), getHeight());
			}

			restoreLocation();
			setAlive(false);
			setRenderActive(false);
			PhysicsObject::onUpdate(dt);
			return;
		}
	}
	if (getRenderActive())
	{
		if (getIsOnGround())
		{
			setVx(-getDirection() * 100);
			setVy(65);
		}
		action = DOG_RUN;
	}

	setAnimation(action);
	PhysicsObject::onUpdate(dt);
}

void Dog::restoreLocation()
{
	BaseObject::restoreLocation();
	setDirectDefault();
}

void Dog::onCollision(MovableRect * other, float collisionTime, int nx, int ny)
{
	if (other->getCollisionType() == COLLISION_TYPE_GROUND)
	{
		setIsOnGround(true);
		preventMovementWhenCollision(collisionTime, nx, ny);
	}
	if (other->getCollisionType() == COLLISION_TYPE_WATER && getRenderActive())
	{
		restoreLocation();
		setRenderActive(false);
		setAlive(false);
	}
	if (other->getCollisionType() == COLLISION_TYPE_PLAYER && getRenderActive())
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

void Dog::setDirectDefault()
{
	if (getMidX() >= 205 && getMidX() <= 270)
	{
		setDirection(TEXTURE_DIRECTION_LEFT);
	}
	else
	if (getMidX() >= 892 && getMidX() <= 927)
	{
			setDirection(TEXTURE_DIRECTION_RIGHT);
	}
	else
	if (getMidX() >= 934 && getMidX() <= 959)
	{
				setDirection(TEXTURE_DIRECTION_LEFT);
	}
	else
	if (getMidX() >= 1248 && getMidX() <= 1315)
	{
					setDirection(TEXTURE_DIRECTION_RIGHT);
	}
}

Dog::Dog()
{
	setAnimation(DOG_WAIT);
	setInterval(200);
	player = Player::getInstance();
	setRenderActive(false);
	setAlive(false);
}

Dog::~Dog()
{
}
