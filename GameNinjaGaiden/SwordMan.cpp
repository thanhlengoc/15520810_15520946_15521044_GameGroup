#include "SwordMan.h"

bool SwordMan::onContactPlayer()
{
	return contactPlayer;
}

void SwordMan::setContactPlayer(bool contactPlayer)
{
	this->contactPlayer = contactPlayer;
}

void SwordMan::setSwordmanState(SWORDMAN_STATE swordmanState)
{
	this->swordmanState = swordmanState;
}

void SwordMan::onUpdate(float dt)
{
	Camera* camera = Camera::getInstance();
	SWORDMAN_ACTION action;
	setVx(0);
	action = SWORDMAN_ACTION_STAND;

	if (player->isDead)
	{
		restoreLocation();
		PhysicsObject::onUpdate(dt);
		return;
	}
	if (abs(getMidX() - camera->getMidX()) > 104)
	{
		setAlive(true);
		setRenderActive(false);
		setFollowPlayer();
	}
	else if(isAlive() && !player->isHurtLeft && !player->isHurtRight)
	{
		setRenderActive(true);
		if (getIsOnDistanceMove())
		{
			action = SWORDMAN_ACTION_RUN_ATTACK;
			double vx = 32;
			TEXTURE_DIRECTION direction;
			if (getDirection() == 1)
			{
				direction = TEXTURE_DIRECTION_LEFT;
			}
			else
			{
				direction = TEXTURE_DIRECTION_RIGHT;
			}
			setDirection(direction);
			setVx(getDirection()*vx);
			setIsOnDistanceMove(false);
			setAnimation(action);
			PhysicsObject::onUpdate(dt);
			return;
		}
		else
		{
			action = SWORDMAN_ACTION_RUN_ATTACK;
			setVx(-getDirection() * 32);
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

			if (abs(getMidX() - player->getMidX()) < 30 && player->isAttack() && (abs(getBottom() - player->getBottom()) < 10))
			{
				restoreLocation();
				setRenderActive(false);
				setAlive(false);

				Weapon* weapon = Weapon::getInstance();
				weapon->setRenderActive(true);

				PhysicsObject::onUpdate(dt);
				return;
			}
		}
	}
	setAnimation(action);	
	PhysicsObject::onUpdate(dt);
}

void SwordMan::onCollision(MovableRect * other, float collisionTime, int nx, int ny)
{
	if (other->getCollisionType() == COLLISION_TYPE_GROUND)
	{
		//van toc khong duoc tang dan deu khi dung tren san
		preventMovementWhenCollision(collisionTime, nx, ny);
	}
	if (other->getCollisionType() == COLLISION_TYPE_DISTANCE_MOVE_ENEMY)
	{
		setIsOnDistanceMove(true);
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
	if (other->getCollisionType() == COLLISION_TYPE_WEAPON)
	{
		//setAlive(false);
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

void SwordMan::resetLocationEmemy()
{
	setAnimation(SWORDMAN_ACTION_STAND);
	set(getInitBox()->getX(), getInitBox()->getY(), getInitBox()->getWidth(), getInitBox()->getHeight());
	setAlive(true);
}

SwordMan::SwordMan()
{
	setAnimation(SWORDMAN_ACTION_STAND);
	setInterval(200);
	player = Player::getInstance();
	player->resetEnemy = dynamic_cast<ResetEnemy*>(this);
	setPhysicsEnable(true);
}

SwordMan::~SwordMan()
{
}
