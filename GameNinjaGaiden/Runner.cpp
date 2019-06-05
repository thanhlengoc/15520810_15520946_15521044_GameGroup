#include "Runner.h"

void Runner::restoreLocation()
{
	BaseObject::restoreLocation();
}

void Runner::onUpdate(float dt)
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
		if (109 <= distanceVisible && distanceVisible <= 110 && !isAlive())
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
		&& (abs(getBottom() - player->getBottom()) < 10)
		&& !player->isHurtLeft && !player->isHurtRight && !player->isDead)
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
		if ((3906 <= getMidX() && getMidX() <= 3908)||(4065 <= getMidX() && getMidX() <= 4067))
		{
			setVy(60);
			setVx(-getDirection() * 100);
		}
		else
		{
			setVx(-getDirection() * 100);
		}
		setAnimation(RUNNER_RUN);
	}

	PhysicsObject::onUpdate(dt);
}

void Runner::onCollision(MovableRect * other, float collisionTime, int nx, int ny)
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

void Runner::setDirectDefault()
{
	if (getMidX() >= 3885 && getMidX() <= 3902)
		setDirection(TEXTURE_DIRECTION_RIGHT);
	else if (getMidX() >= 3917 && getMidX() <= 3933)
		setDirection(TEXTURE_DIRECTION_LEFT);
	else if (getMidX() >= 3945 && getMidX() <= 3961)
		setDirection(TEXTURE_DIRECTION_RIGHT);
}

Runner::Runner()
{
	setAnimation(RUNNER_WAIT);
	player = Player::getInstance();
	weapon_player = WeaponPlayer::getInstance();
	setRenderActive(false);
	setAlive(false);
	setDirectDefault();
}

Runner::~Runner()
{
}
