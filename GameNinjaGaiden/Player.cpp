#include "Player.h"
#include"ScoreBar.h"

Player * Player::instance = 0;
Player * Player::getInstance()
{
	if (instance == 0)
	{
		instance = new Player();
	}
	return instance;
}

void Player::onUpdate(float dt)
{
	PLAYER_ACTION action;
	double vx = GLOBALS_D("player_vx");
	double vy = GLOBALS_D("player_vy_jump");
	endDeadTime = false;

	setInterval(60);
	action = PLAYER_ACTION_STAND;

	switch (changeSpace->getCurrentSpaceIndex())
	{
	case 0:
		ScoreBar::getInstance()->setCurrentStageNumber(01);
		break;
	case 2:
		ScoreBar::getInstance()->setCurrentStageNumber(02);
		break;
	case 5:
		ScoreBar::getInstance()->setCurrentStageNumber(03);
		break;
	default:
		break;
	}

	if (ScoreBar::getInstance()->getHealth() <= 0)
	{
		if (lostHeal)
		{
			deadDelay.start();
			isDead = true;
			lostHeal = false;
		}
	}
	if (ScoreBar::getInstance()->getTime() <= 0)
	{
		if (restartTime)
		{
			deadDelay.start();
			isDead = true;
			restartTime = false;
		}
	}

	if (isHurtLeft || isHurtRight)
	{
		if (decreaseHeal)
		{
			ScoreBar::getInstance()->decreaseHealth(1);
			decreaseHeal = false;
		}
		setIsOnLadder(false);
		setAy(GLOBALS_D("object_default_ay"));
		setPhysicsEnable(true);
		if (hurtDelay.isTerminated())
		{
			decreaseHeal = true;
			setAnimation(PLAYER_ACTION_STAND);
			isHurtLeft = isHurtRight = false;
		}
		if (!hurtDelay.isOnTime())
		{
			if (getIsOnGround())
			{
				if (isHurtLeft)
				{
					setVx(52);
					setVy(180);
				}
				else if (isHurtRight)
				{
					setVx(-52);
					setVy(180);
				}
				setAnimation(PLAYER_ACTION_HURT);
			}
			else
			{
				if (isHurtLeft)
				{
					setVx(52);
					setVy(120);
				}
				else if (isHurtRight)
				{
					setVx(-52);
					setVy(120);
				}
				setAnimation(PLAYER_ACTION_HURT);
				hurtDelay.start();
			}
		}
		else if (hurtDelay.isOnTime())
		{
			if (getIsOnGround())
			{
				setVx(0);
				setVy(0);
				setHeight(GLOBALS_D("player_height"));
				setAnimation(PLAYER_ACTION_RESET);
			}
			hurtDelay.update();
		}
		PhysicsObject::onUpdate(dt);
		return;
	}

	if (isDead)
	{
		setAnimation(PLAYER_ACTION_DIE);
		setDx(0);
		setVx(0);
		setDy(0);
		setVy(0);
		setHeight(getCurrentFrameHeight());

		deadDelay.update();
		if (deadDelay.isTerminated())
		{
			setRenderActive(false);
			int currentSpaceIndex = changeSpace->getCurrentSpaceIndex();
			if (currentSpaceIndex == 5)
			{
				changeSpace->setCurrentSpace(2);
				changeSpace->resetLocationInSpace();
			}
			else
			{
				changeSpace->setCurrentSpace(currentSpaceIndex);
				changeSpace->resetLocationInSpace();
			}

			ScoreBar::getInstance()->restoreHealth();
			ScoreBar::getInstance()->restoreBossHealth();

			int countLife = ScoreBar::getInstance()->getPlayerLife();
			if (countLife == 0)
			{
				ScoreBar::getInstance()->setPlayerLife(2);
				ScoreBar::getInstance()->setScore(0);
			}
			else
			{
				ScoreBar::getInstance()->setPlayerLife(countLife - 1);
			}

			endDeadTime = true;
			isDead = false;
			lostHeal = true;
			restartTime = true;
			setDirection(TEXTURE_DIRECTION_RIGHT);
			setRenderActive(true);
		}
		//PhysicsObject::onUpdate(dt);
		return;
	}

	if (getIsLastFrameAnimationDone() && isOnAttack)
	{
		setIsOnAttack(false);
	}

	if (key->isAttackPress && !getIsOnLadder())
	{
		setIsOnAttack(true);
	}

	if (getIsOnLadder())
	{
		setHeight(GLOBALS_D("player_height"));
		setAy(0);

		if (getY() > 135)
		{
			setAnimation(PLAYER_ACTION_CLIMB_WAIT);
			setY(135);
		}
		if (key->isUpDown)
		{
			setVy(55);
			setAnimation(PLAYER_ACTION_CLIMB);
		}
		else if (key->isDownDown)
		{
			setVy(-55);
			setAnimation(PLAYER_ACTION_CLIMB);
		}
		else if (key->isJumpDown)
		{
			setVy(vy);
			setVx(-getDirection() * vx);
			setIsOnLadder(false);
			setAy(GLOBALS_D("object_default_ay"));
			setPhysicsEnable(true);
		}
		else
		{
			setDx(0);
			setDy(0);
			setVx(0);
			setVy(0);
			setAnimation(PLAYER_ACTION_CLIMB_WAIT);
		}
		PhysicsObject::onUpdate(dt);
		return;
	}
	if (getIsOnGround())
	{
		setHeight(GLOBALS_D("player_height"));
		if (key->isLeftDown)
		{
			setDirection(TEXTURE_DIRECTION_LEFT);
		}
		if (key->isRightDown)
		{
			setDirection(TEXTURE_DIRECTION_RIGHT);
		}
		if (key->isDownDown)
		{
			action = PLAYER_ACTION_SIT;
			setHeight(GLOBALS_D("player_sit"));
			setVx(0);

			if (isOnAttack)
			{
				setHeight(25);
				action = PLAYER_ACTION_SIT_ATTACK;
			}
		}
		else
		{
			bool isMoveDown = key->isLeftDown || key->isRightDown;
			if (isMoveDown)
			{
				setVx(getDirection() * vx);
				action = PLAYER_ACTION_RUN;
			}
			else
			{
				setVx(0);
				action = PLAYER_ACTION_STAND;
			}

			if (isOnAttack)
			{
				action = PLAYER_ACTION_ATTACK;
				setInterval(80);
			}

			if (key->isJumpPress)
			{
				setVy(vy);
			}
		}
	}
	else
	{
		setHeight(GLOBALS_D("player_jump_height"));
		action = PLAYER_ACTION_JUMP;

		if (isOnAttack)
		{
			action = PLAYER_ACTION_ATTACK;
			setVx(0);
		}
		if (key->isLeftDown)
		{
			setDirection(TEXTURE_DIRECTION_LEFT);
			setVx(-50);
		}
		else if (key->isRightDown)
		{
			setDirection(TEXTURE_DIRECTION_RIGHT);
			setVx(50);
		}
		else
		{
			setVx(0);
		}
	}
	if (isOnAttack && getIsOnGround())
	{
		setVx(0);

	}

	setAnimation(action);
	PhysicsObject::onUpdate(dt);
}

void Player::onCollision(MovableRect * other, float collisionTime, int nx, int ny)
{
	if (other->getCollisionType() == COLLISION_TYPE_GROUND)
	{
		if (ny == 1)
		{
			setIsOnGround(true);
		}

		if (ny != 0)
		{
			setVy(-10);
		}
		if(!getIsOnLadder())
			preventMovementWhenCollision(collisionTime, nx, ny);
	}

	if (other->getCollisionType() == COLLISION_TYPE_WATER)
	{
		deadDelay.start();
		isDead = true;
	}
	if (other->getCollisionType() == COLLISION_TYPE_GATE)
	{
		if (changeSpace->getCurrentSpaceIndex() == 0)
		{
			changeSpace->setCurrentSpace(3);
			changeSpace->resetLocationInSpace();
		}
		else if (changeSpace->getCurrentSpaceIndex() == 2)
		{
			changeSpace->setCurrentSpace(4);
			changeSpace->resetLocationInSpace();
		}
	}
	if (other->getCollisionType() == COLLISION_TYPE_LADDER)
	{
		setIsOnLadder(true);
		preventMovementWhenCollision(collisionTime, nx, ny);
	}
	if (other->getCollisionType() == COLLISION_TYPE_WOOD_BAR)
	{
		if (getY() > 110)
		{
			if (ny == 1)
			{
				setIsOnGround(true);
			}

			if (ny != 0)
			{
				setVy(-10);
			}
			if (!getIsOnLadder())
				preventMovementWhenCollision(collisionTime, nx, ny);
		}
	}
	PhysicsObject::onCollision(other, collisionTime, nx, ny);
}

void Player::startDeadTime()
{
	deadDelay.start();
}

void Player::setIsOnAttack(bool isOnAttack)
{
	this->isOnAttack = isOnAttack;
}

bool Player::isAttack()
{
	return isOnAttack;
}

int Player::getSpacePlayer()
{
	return changeSpace->getCurrentSpaceIndex();
}

Player::Player()
{
	setSprite(SPR(SPRITE_INFO_RYU));
	setCollisionType(COLLISION_TYPE_PLAYER);
	key = KEY::getInstance();
	setDirection(TEXTURE_DIRECTION_RIGHT);
	setAnimation(PLAYER_ACTION_STAND);
	isDead = false;
	isHurtLeft = isHurtRight = false;
	setAlive(true);
	deadDelay.init(GLOBALS_D("player_dead_delay"));
	hurtDelay.init(1200);
	endDeadTime = false;
	decreaseHeal = true;
	lostHeal = true;
	restartTime = true;
}


Player::~Player()
{
}
