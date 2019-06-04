#include "Bat.h"

void Bat::onUpdate(float dt)
{
	setFollowPlayer();
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
	if (distanceVisible >= 110)
	{
		setRenderActive(true);
		setAlive(true);
	}
	if (abs(getMidX() - player->getMidX()) < 36 && player->isAttack() && (abs(getMidY() - player->getMidY()) < 15)
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
	PhysicsObject::onUpdate(dt);
}

void Bat::onCollision(MovableRect* other, float collisionTime, int nx, int ny)
{

	PhysicsObject::onCollision(other, collisionTime, nx, ny);
}

void Bat::setFollowPlayer()
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

Bat::Bat()
{
	setPhysicsEnable(false);
	setAnimation(BAT_FLY);
	player = Player::getInstance();
	weapon_player = WeaponPlayer::getInstance();
	camera = Camera::getInstance();
}

Bat::~Bat()
{
}
