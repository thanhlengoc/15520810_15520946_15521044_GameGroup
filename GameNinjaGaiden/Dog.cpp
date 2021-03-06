#include "Dog.h"
#include "ScoreBar.h"

void Dog::onUpdate(float dt)
{
	Camera* camera = Camera::getInstance();

	if (player->endDeadTime)
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
			setDirectDefault();
			PhysicsObject::onUpdate(dt);
			return;
		}
	}
	else
	{
		restoreLocation();
		setAlive(false);
		setRenderActive(false);
		setDirectDefault();
		PhysicsObject::onUpdate(dt);
		return;
	}
	if ((abs(getMidX() - player->getMidX()) < 18) && getRenderActive()
		&& (abs(getBottom() - player->getBottom()) < 10)
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
			ScoreBar::getInstance()->increaseScore(300);
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
	if (other->getCollisionType() == COLLISION_TYPE_STAR && getRenderActive())
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

		restoreLocation();
		setVx(0);
		setAlive(false);
		setRenderActive(false);
		ScoreBar::getInstance()->increaseScore(300);
	}
	if (other->getCollisionType() == COLLISION_TYPE_PLAYER && getRenderActive()
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
	PhysicsObject::onCollision(other, collisionTime, nx, ny);
}

void Dog::setDirectDefault()
{
	if (getMidX() >= 205 && getMidX() <= 270)
		setDirection(TEXTURE_DIRECTION_LEFT);
	else if (getMidX() >= 892 && getMidX() <= 927)
		setDirection(TEXTURE_DIRECTION_RIGHT);
	else if (getMidX() >= 934 && getMidX() <= 959)
		setDirection(TEXTURE_DIRECTION_LEFT);
	else if (getMidX() >= 1248 && getMidX() <= 1315)
		setDirection(TEXTURE_DIRECTION_RIGHT);
	else if (getMidX() >= 5000 && getMidX() <= 5188)
		setDirection(TEXTURE_DIRECTION_LEFT);
	else if (getMidX() >= 5333 && getMidX() <= 5350)
		setDirection(TEXTURE_DIRECTION_RIGHT);
}

Dog::Dog()
{
	setAnimation(DOG_WAIT);
	setInterval(200);
	player = Player::getInstance();
	weapon_player = WeaponPlayer::getInstance();
	setRenderActive(false);
	setAlive(false);
	setDirectDefault();
}

Dog::~Dog()
{
}
