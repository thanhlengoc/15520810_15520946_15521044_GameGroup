#include "Boss.h"
#include"ScoreBar.h"


void Boss::setState(BOSS_STATE bossState)
{
	this->bossState = bossState;
}

void Boss::onUpdate(float dt)
{
	if (ScoreBar::getInstance()->getBossHealth() == 0)
		setState(BOSS_STATE_DEAD);

	switch (bossState)
	{
	case BOSS_STATE_WAIT:
		setAnimation(BOSS_STAND);
		if (getIsLastFrameAnimationDone())
			count++;
		if (count > 5)
		{
			setVy(303);
			setVx(-getDirection() * 110);
			count = 0;
			setState(BOSS_STATE_JUMP);
		}
		break;
	case BOSS_STATE_JUMP:

		setAnimation(BOSS_JUMP);

		if (getIsOnGround())
		{
			setState(BOSS_STATE_WAIT);
			setAnimation(BOSS_STAND);

			if (getRenderActive())
			{
				/*
				BossWeapon* bl = new BossWeapon();
				bl->setX(getX() + (getDirection() * 10));
				bl->setY(getY() - 30);
				bl->setDirection(getDirection());
				bl->setVx(getDirection() * GLOBALS_D("boss_weapon_vx"));
				*/
			}


		}
		break;

	case BOSS_STATE_INJURE:
		setAnimation(BOSS_STAND);
		if (getIsLastFrameAnimationDone())
			count++;
		if (count > 2)
		{
			setState(BOSS_STATE_JUMP);
			count = 0;
		}
		break;

	case BOSS_STATE_DEAD:
		setAnimation(BOSS_DIE);
		setVx(0);
		setVy(0);

		/*
		if (getIsLastFrameAnimationDone())
			count++;
		if (count >= 4)
			count = 0;
		break;
		*/
	}
	PhysicsObject::onUpdate(dt);
}

void Boss::onCollision(MovableRect* other, float collisionTime, int nx, int ny)
{
	if (other->getCollisionType() == COLLISION_TYPE_GROUND)
	{
		setIsOnGround(true);
		preventMovementWhenCollision(collisionTime, nx, ny);
		setFollowPlayer();
		setVy(0);
	}
}

void Boss::setFollowPlayer()
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

Boss::Boss()
{
	setAnimation(BOSS_STAND);
	player = Player::getInstance();
	setState(BOSS_STATE_WAIT);
	setPhysicsEnable(true);
}

Boss::~Boss()
{
}
