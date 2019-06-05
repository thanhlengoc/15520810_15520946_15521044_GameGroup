#include "Bird.h"

void Bird::onUpdate(float dt)
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
	if (getDirection() == 1)
	{
		if (108 <= distanceVisible && distanceVisible <= 110 && !isAlive())
		{
			setRenderActive(true);
			setAlive(true);
		}
	}
	else
	{
		if (-110 <= distanceVisible && distanceVisible <= -108 && !isAlive())
		{
			setRenderActive(true);
			setAlive(true);
		}
	}
	if (isAlive())
	{
		if (abs(getMidX() - camera->getMidX()) >= 150)
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
		&& (abs(getBottom() - player->getBottom()) < 15)
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

	if (abs(getMidX() - player->getMidX()) < 36 && player->isAttack() && (abs(getBottom() - player->getBottom()) < 15)
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

			restoreLocation();
			setVx(0);
			setAlive(false);
			setRenderActive(false);
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
		switch (birdState)
		{
		case BIRD_WAIT:
			if (getX() - player->getX() < 100)
				setState(BIRD_FLY);
			break;
		case BIRD_FLY:
			setVy(player->getY() - getY() - 80);
			setVx(player->getX() - getX() - 80);
			if (player->getY() - getY() > 10 && player->getY() - getY() > 10)
			{
				setAx(50);
				setAy(10);
				setVy(-20);
			}
			if (player->getX() - getX() > 40)
			{
				setVx((player->getMidX() - getMidX()) * 2);
				setVy((50 - getMidY()) * 2);
				setDirection(TEXTURE_DIRECTION_LEFT);
				setState(BIRD_FIRST_FLY);
			}
			break;
		case BIRD_FIRST_FLY:
			if (getMidX() > player->getMidX())
			{
				setAy(-50);
				setAx(-100);
				setState(BIRD_FLY_DOWN_RIGHT);
			}
			break;
		case BIRD_FLY_DOWN_RIGHT:
			setFollowPlayer();
			if (getMidY() >= 80)
			{
				setVy(-50);
				setVx(50);
				setState(BIRD_FLY_UP_RIGHT);
			}
			break;
		case BIRD_FLY_UP_RIGHT:
			if (getY() < 10) {
				setVx(-(getMidX() - player->getMidX()) * 2);
				setVy((50 - getMidY()) * 2);
				setState(BIRD_SECOND_FLY);
			}
			break;
		case BIRD_SECOND_FLY:
			if (getMidX() < player->getMidX())
			{
				setAy(-50);
				setAx(100);
				setState(BIRD_FLY_DOWN_LEFT);
			}
			break;
		case BIRD_FLY_DOWN_LEFT:
			setFollowPlayer();
			if (getMidY() >= 80)
			{
				setVy(-50);
				setVx(-50);
				setState(BIRD_FLY_UP_LEFT);
			}
			break;
		case BIRD_FLY_UP_LEFT:
			if (getY() < 10) {
				setVx((player->getMidX() - getMidX()) * 2);
				setVy((50 - getMidY()) * 2);
				setState(BIRD_FIRST_FLY);
			}
			break;
		}
		setAnimation(BIRD_FLY);
	}
	PhysicsObject::onUpdate(dt);
}

void Bird::restoreLocation()
{
	BaseObject::restoreLocation();
	setDirectDefault();
}

void Bird::onCollision(MovableRect* other, float collisionTime, int nx, int ny)
{
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

void Bird::setDirectDefault()
{
	if (getMidX() >= 541 && getMidX() <= 576)
		setDirection(TEXTURE_DIRECTION_RIGHT);
	else if (getMidX() >= 706 && getMidX() <= 734)
		setDirection(TEXTURE_DIRECTION_RIGHT);
	else if (getMidX() >= 1047 && getMidX() <= 1068)
		setDirection(TEXTURE_DIRECTION_LEFT);
	else if (getMidX() >= 1558 && getMidX() <= 1594)
		setDirection(TEXTURE_DIRECTION_LEFT);
	else if (getMidX() >= 1690 && getMidX() <= 1709)
		setDirection(TEXTURE_DIRECTION_LEFT);
	else if (getMidX() >= 1868 && getMidX() <= 1904)
		setDirection(TEXTURE_DIRECTION_RIGHT);
	else if (getMidX() >= 3211 && getMidX() <= 3247)
		setDirection(TEXTURE_DIRECTION_LEFT);
	else if (getMidX() >= 3748 && getMidX() <= 3765)
		setDirection(TEXTURE_DIRECTION_RIGHT);
	else if (getMidX() >= 4711 && getMidX() <= 4730)
		setDirection(TEXTURE_DIRECTION_RIGHT);
	else if (getMidX() >= 4976 && getMidX() <= 5000)
		setDirection(TEXTURE_DIRECTION_RIGHT);
	else if (getMidX() >= 5300 && getMidX() <= 5320)
		setDirection(TEXTURE_DIRECTION_RIGHT);
}

void Bird::setState(BIRD_STATE birdState)
{
	this->birdState = birdState;
}

void Bird::setFollowPlayer()
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

Bird::Bird()
{
	setAy(0);
	setAnimation(BIRD_WAIT);
	setState(BIRD_WAIT);
	player = Player::getInstance();
	weapon_player = WeaponPlayer::getInstance();
	setRenderActive(false);
	setAlive(false);
	setDirectDefault();
}

Bird::~Bird()
{
}
