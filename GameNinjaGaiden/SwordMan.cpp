#include "SwordMan.h"

void SwordMan::onUpdate(float dt)
{
	Player* player = Player::getInstance();
	SWORDMAN_ACTION action;

	setFollowPlayer();
	action = SWORDMAN_ACTION_STAND;
	setVx(0);
	setInterval(GLOBALS_D("enemy_animation_time_default"));
	isOnAttack = false;
	if (isDead)
	{
		if (tickTime == 0)
		{
			setX((getX() + 26)*getDirection());
			setY(getY() + 5);
		}
		tickTime++;
		setVx(0);
		setAnimation(SWORDMAN_ACTION_DIE);

		deadTime.update();
		if (deadTime.isTerminated())
			setAlive(false);
		return;
	}
	else
	if (abs(getMidX() - Player::getInstance()->getMidX()) < GLOBALS_D("zombie_distance_to_activity") && !player->isDead && !isDead)
	{
		action = SWORDMAN_ACTION_RUN_ATTACK;
		setVx(-getDirection() * 40);
		setFollowPlayer();
		if (abs(getMidX() - Player::getInstance()->getMidX()) < 23)
		{
			if (player->isAttack() && isAlive())
			{
				deadTime.start();
				isDead = true;
			}
		}
		if (abs(getMidX() - Player::getInstance()->getMidX()) < 18 && isAlive())
		{
			setVx(0);
			isOnAttack = true;
		}
	}
	else
	{
		action = SWORDMAN_ACTION_STAND;
		setVx(0);
	}
	if (isOnAttack && getIsLastFrameAnimationDone())
	{
		player->isDead = true;
		player->startDeadDelay();
		player->update(dt);
	}
	
	setAnimation(action);

	
	PhysicsObject::onUpdate(dt);
}

void SwordMan::onCollision(MovableRect * other, float collisionTime, int nx, int ny)
{
	PhysicsObject::onCollision(other, collisionTime, nx, ny);
}

void SwordMan::setFollowPlayer()
{
	int distance = Player::getInstance()->getMidX() - getMidX();
	if (distance < 0)
	{
		setDirection(TEXTURE_DIRECTION_RIGHT);
	}
	else
	{
		setDirection(TEXTURE_DIRECTION_LEFT);
	}
}

void SwordMan::restoreLocation()
{
	BaseObject::restoreLocation();
}

SwordMan::SwordMan()
{
	setAnimation(SWORDMAN_ACTION_STAND);
	deadTime.init(200);
	isOnAttack = false;
	setAlive(true);
	isDead = false;
	tickTime = 0;
	setVx(0);
}

SwordMan::~SwordMan()
{
}
