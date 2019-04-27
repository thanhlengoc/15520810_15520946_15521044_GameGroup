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
	double vx = GLOBALS_D("player_vx");
	double vy = GLOBALS_D("player_vy_jump");

	setInterval(60);
	action = PLAYER_ACTION_STAND;

	if (isHurtLeft || isHurtRight)
	{
		if (hurtDelay.isTerminated())
		{
			setAnimation(PLAYER_ACTION_STAND);
			isHurtLeft = isHurtRight = false;
		}
		if (!hurtDelay.isOnTime())
		{
			if (getIsOnGround())
			{
				if (isHurtLeft)
				{
					setVx(32);
					setVy(107);
				}
				else if (isHurtRight)
				{
					setVx(-32);
					setVy(107);
				}
				setAnimation(PLAYER_ACTION_HURT);
			}
			else
			{
				if (isHurtLeft)
				{
					setVx(32);
					setVy(60);
				}
				else if (isHurtRight)
				{
					setVx(-32);
					setVy(60);
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
		else if(key->isRightDown)
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
		//van toc khong duoc tang dan deu khi dung tren san
		if (ny == 1)
		{
			setIsOnGround(true);
		}

		if (ny != 0)
		{
			setVy(-10);
		}
		preventMovementWhenCollision(collisionTime, nx, ny);
	}
	
	if (other->getCollisionType() == COLLISION_TYPE_WATER)
	{
		deadDelay.start();
		isDead = true;
	}
	if (other->getCollisionType() == COLLISION_TYPE_GATE)
	{
		changeSpace->setCurrentSpace(3);
		changeSpace->resetLocationInSpace();		
	}
	PhysicsObject::onCollision(other, collisionTime, nx, ny);
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
	setCollisionType(COLLISION_TYPE_PLAYER);
	key = KEY::getInstance();
	setDirection(TEXTURE_DIRECTION_RIGHT);
	setAnimation(PLAYER_ACTION_STAND);
	isDead = false;
	isHurtLeft = isHurtRight = false;
	setAlive(true);
	deadDelay.init(GLOBALS_D("player_dead_delay"));
	hurtDelay.init(900);
}


Player::~Player()
{
}
