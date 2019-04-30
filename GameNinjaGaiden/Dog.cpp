#include "Dog.h"

void Dog::onUpdate(float dt)
{
	Camera* camera = Camera::getInstance();

	setDirectDefault();

	if (player->isDead)
	{
		restoreLocation();
		setRenderActive(false);
		setVx(0);
		setAlive(false);
		PhysicsObject::onUpdate(dt);
		return;
	}
	float distanceVisible = getMidX() - camera->getMidX();
	if (getDirection()==1)
	{
		if (109<=distanceVisible && distanceVisible<=110 && !isAlive())
		{
			setRenderActive(true);
			setAlive(true);
		}
	}
	else
	{
		if (-110 <= distanceVisible && distanceVisible <= -109 && !isAlive())
		{
			setRenderActive(true);
			setAlive(true);
		}
	}
	if (isAlive())
	{
		if (abs(getMidX() - camera->getMidX()) >= 155)
		{
			restoreLocation();
			setAlive(false);
			setRenderActive(false);
			PhysicsObject::onUpdate(dt);
			return;
		}
	}
	else
	{
		restoreLocation();
		setAlive(false);
		setRenderActive(false);
		PhysicsObject::onUpdate(dt);
		return;
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
			weapon_player->setRenderActive(true);
			if (getDirection() == 1)
			{
				weapon_player->setLocation(getMidX() + 15, getY()+15);
			}
			else
			{
				weapon_player->setLocation(getMidX() + 10, getY()+15);
			}
			weapon_player->startAnimationWeapon();

			restoreLocation();
			setVx(0);
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
			setVx(-getDirection() * 97);
			setVy(90);
		}
		setAnimation(DOG_RUN);
	}

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
	if (other->getCollisionType() == COLLISION_TYPE_WATER_SURFACE && getRenderActive() && isAlive())
	{
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
	weapon_player = WeaponPlayer::getInstance();
	setRenderActive(false);
	setAlive(false);
}

Dog::~Dog()
{
}
