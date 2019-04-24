#include "Enemy.h"
#include "Player.h"

void Enemy::setHealth(int health)
{
	this->health = health;
}

int Enemy::getHealth()
{
	return health;
}

void Enemy::setDirectionFollowPlayer()
{
	if (Player::getInstance()->getMidX() - getMidX() < 0)
	{
		setDirection(TEXTURE_DIRECTION_LEFT);
	}
	else
	{
		setDirection(TEXTURE_DIRECTION_RIGHT);
	}
}

void Enemy::onDeath()
{
}

void Enemy::onDecreaseHealth()
{
}

void Enemy::onCollision(MovableRect * other, float collisionTime, int nx, int ny)
{
	PhysicsObject::onCollision(other, collisionTime, nx, ny);
}

void Enemy::onIntersect(MovableRect * other)
{
	//xu ly khi enemy cham vao player
	auto player = Player::getInstance();

	if (other == player && canAttackPlayer() && !player->isDead)
	{
		onContactPlayer();
		player->isDead = true;
		//player->startDeadDelay();
	}
}

void Enemy::restoreLocation()
{
	setHealth(1);
	BaseObject::restoreLocation();
}

void Enemy::onContactPlayer()
{
	auto player = Player::getInstance();
	auto camera = Camera::getInstance();


	player->setAnimation(PLAYER_ACTION_DIE);
	player->setIsOnGround(false);
	player->setDy(0);
	
	if (player->getX() > this->getX())
	{
		player->setVx(GLOBALS_D("player_hit_vx"));
	}
	else
	{
		player->setVx(-GLOBALS_D("player_hit_vx"));
	}

}

void Enemy::onContactWeapon()
{
	setHealth(getHealth() - 1);
	onDecreaseHealth();
	if (getHealth() <= 0)
	{
		this->setAlive(false);
		onDeath();
	}
}

bool Enemy::canAttackPlayer()
{
	return this->getRenderActive();
}

Enemy::Enemy()
{
	setHealth(1);
}

Enemy::~Enemy()
{
}
