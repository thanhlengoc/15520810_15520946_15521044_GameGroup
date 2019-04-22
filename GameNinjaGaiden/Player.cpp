#include "Player.h"

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
	
	setInterval(60);
	if (isDead)
	{
		setAnimation(PLAYER_ACTION_DIE);
		setDx(0);
		setVx(0);
		setDy(0);
		setVy(60);
		setHeight(getCurrentFrameHeight());

		deadDelay.update();
		if (deadDelay.isTerminated())
		{
			int currentSpaceIndex = changeSpace->getCurrentSpaceIndex();
			changeSpace->setCurrentSpace(currentSpaceIndex);
			changeSpace->resetLocationInSpace();
			isDead = false;
		}
		return;
	}
	
	if (getIsLastFrameAnimationDone() && isOnAttack)
	{
		setIsOnAttack(false);
	}
	if (key->isAttackPress)
	{
		setIsOnAttack(true);
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
			double vx = GLOBALS_D("player_vx");
			double vy = GLOBALS_D("player_vy_jump");

			bool isMoveDown = key->isLeftDown || key->isRightDown;
			if (isMoveDown)
			{
				setVx(getDirection()*vx);
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
				if (isMoveDown)
				{
					setVx(getDirection() * 89);
					setVy(vy);
				}
				else
				{
					setVy(vy);
				}
				
			}
		}
	}
	else
	{
		setHeight(GLOBALS_D("player_jump_height"));
		action = PLAYER_ACTION_JUMP;	
		if (isOnAttack)
		{
			action = PLAYER_ACTION_JUMP_ATTACK;
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
	if (other->getCollisionType() == COLLISION_TYPE_WATER)
	{
		isDead = true;
	}
	PhysicsObject::onCollision(other, collisionTime, nx, ny);
}

void Player::startDeadDelay()
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

Player::Player()
{
	setSprite(SPR(SPRITE_INFO_RYU));
	key = KEY::getInstance();
	setDirection(TEXTURE_DIRECTION_RIGHT);
	setAnimation(PLAYER_ACTION_STAND);
	isDead = false;
	setAlive(true);
	deadDelay.init(GLOBALS_D("player_dead_delay"));
}


Player::~Player()
{
}
