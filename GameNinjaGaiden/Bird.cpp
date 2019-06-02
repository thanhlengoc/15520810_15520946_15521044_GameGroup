#include "Bird.h"

void Bird::onUpdate(float dt)
{
	Camera* camera = Camera::getInstance();

	setDirectDefault();

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
	if (getRenderActive())
	{
		
		if (getMidY() > (player->getMidY()-50) && isInit)
		{
			setVx(-getDirection() * 150);
			setVy(-150);
			setDx(getVx() * dt);
			setDy(getVy() * dt);
			isWait = false;
			changeDirection = true;
		}
		else
		{
			isInit = false;
			if (!isWait)
			{
				if (changeDirection)
				{
					setFollowPlayer();
					changeDirection = false;
				}
				setVx(-getDirection() * 150);
				setVy(150);
				setDx(getVx()* dt);
				setDy(getVy()* dt);
			}
			
			if (getMidY() > (player->getMidY() + 150))
			{
				isWait = true;
				isInit = true;
			}
			
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
	setPhysicsEnable(false);
	setAnimation(BIRD_WAIT);
	player = Player::getInstance();
	weapon_player = WeaponPlayer::getInstance();
	setRenderActive(false);
	setAlive(false);
	isInit = true;
	waitFlyTime.init(1000);
	isWait = false;
	changeDirection = true;
}

Bird::~Bird()
{
}
