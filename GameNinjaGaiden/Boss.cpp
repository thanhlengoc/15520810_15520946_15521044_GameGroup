#include "Boss.h"
#include"ScoreBar.h"


void Boss::setState(BOSS_STATE bossState)
{
	this->bossState = bossState;
}

void Boss::onUpdate(float dt)
{
	if (player->getSpacePlayer() == 5)
	{
		if (ScoreBar::getInstance()->getBossHealth() == 0)
			setState(BOSS_STATE_DEAD);

		if (player->isDead)
		{
			setAnimation(BOSS_STAND);
			setVx(0);
			setVy(0);
			PhysicsObject::onUpdate(dt);
			return;
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

				if (isInjureActive)
				{
					ScoreBar::getInstance()->increaseBossHealth(-1);
					isInjureActive = false;
				}
			}
		}

		switch (bossState)
		{
		case BOSS_STATE_WAIT:
			setAnimation(BOSS_STAND);
			if (getIsLastFrameAnimationDone())
				countEnd++;
			if (countEnd > 5)
			{
				setVy(303);
				setVx(-getDirection() * 110);
				countEnd = 0;
				setState(BOSS_STATE_JUMP);
			}
			break;
		case BOSS_STATE_JUMP:

			setAnimation(BOSS_JUMP);

			if (getIsOnGround())
			{
				isInjureActive = true;
				setState(BOSS_STATE_WAIT);
				setAnimation(BOSS_STAND);

				if (getRenderActive())
				{
					weapon_first->setLocation(getMidX(), getMidY());
					weapon_first->setVx(-getDirection() * 32);
					weapon_first->setDx(-getDirection() * 2);
					weapon_first->setAnimation(WEAPON_SHOT);
					weapon_first->setDirection(getDirection());
					weapon_first->setRenderActive(true);
					weapon_first->setSprite(SPR(SPRITE_INFO_BOSS_WEAPON));
					weapon_first->onUpdate(dt);

					weapon_second->setLocation(getMidX() - 10, getMidY() - 10);
					weapon_second->setVx(-getDirection() * 32);
					weapon_second->setDx(-getDirection() * 2);
					weapon_second->setAnimation(WEAPON_SHOT);
					weapon_second->setDirection(getDirection());
					weapon_second->setRenderActive(true);
					weapon_second->setSprite(SPR(SPRITE_INFO_BOSS_WEAPON));
					weapon_second->onUpdate(dt);

					weapon_three->setLocation(getMidX() + 10, getMidY() + 10);
					weapon_three->setVx(-getDirection() * 32);
					weapon_three->setDx(-getDirection() * 2);
					weapon_three->setAnimation(WEAPON_SHOT);
					weapon_three->setDirection(getDirection());
					weapon_three->setRenderActive(true);
					weapon_three->setSprite(SPR(SPRITE_INFO_BOSS_WEAPON));
					weapon_three->onUpdate(dt);
				}
			}
			break;

		case BOSS_STATE_INJURE:
			setAnimation(BOSS_STAND);
			if (getIsLastFrameAnimationDone())
				countEnd++;
			if (countEnd > 2)
			{
				setState(BOSS_STATE_JUMP);
				countEnd = 0;
			}
			break;

		case BOSS_STATE_DEAD:
			setAnimation(BOSS_DIE);
			setVx(0);
			setVy(0);

			if (getIsLastFrameAnimationDone())
				countEnd++;
			if (countEnd >= 3)
				setRenderActive(false);
			break;
		}
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
	weapon_first = WeaponShot::getInstance();
	weapon_second = WeaponShotSecond::getInstance();
	weapon_three = WeaponShotThree::getInstance();
	weapon_player = WeaponPlayer::getInstance();
	isInjureActive = true;
}

Boss::~Boss()
{
}
