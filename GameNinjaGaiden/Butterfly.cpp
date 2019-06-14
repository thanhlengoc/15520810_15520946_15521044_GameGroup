#include "Butterfly.h"
#include"ScoreBar.h"

void Butterfly::setFollowPlayer()
{
	int distance = player->getMidX() - getMidX();
	if (distance < 0)
	{
		setDirection(TEXTURE_DIRECTION_LEFT);
	}
	else
	{
		setDirection(TEXTURE_DIRECTION_RIGHT);
	}
}

void Butterfly::onUpdate(float dt)
{
	if (player->endDeadTime)
	{
		restoreLocation();
		setRenderActive(true);
		setPhysicsEnable(false);
		setAnimation(BUTTERFLY_FLY);
		PhysicsObject::onUpdate(dt);
		return;
	}

	setFollowPlayer();

	if (getAnimation() == BUTTERFLY_FLY || getAnimation() == BUTTERFLY_WAIT)
	{
		setPhysicsEnable(false);

		if (player->isDead || player->getFreezeTime())
			setAnimation(BUTTERFLY_WAIT);
		else
			setAnimation(BUTTERFLY_FLY);

		if (abs(getMidX() - player->getMidX()) < 25 && player->isAttack() 
			&& abs(getMidY() - player->getMidY()) < 10)
		{
			if (336 < getMidX() && getMidX() < 351)
				setAnimation(BUTTERFLY_SpiritualStrengthBlue);
			else if (425 < getMidX() && getMidX() < 440)
				setAnimation(BUTTERFLY_SpiritualStrengthBlue);
			else if (574 < getMidX() && getMidX() < 590)
				setAnimation(BUTTERFLY_SpiritualStrengthRed);
			else if (634 < getMidX() && getMidX() < 659)
				setAnimation(BUTTERFLY_TimeFreeze);
			else if (762 < getMidX() && getMidX() < 777)
				setAnimation(BUTTERFLY_ThrowingStar);
			else if (895 < getMidX() && getMidX() < 910)
				setAnimation(BUTTERFLY_BonusRed);
			else if (1149 < getMidX() && getMidX() < 1164)
				setAnimation(BUTTERFLY_SpiritualStrengthRed);
			else if (1325 < getMidX() && getMidX() < 1340)
				setAnimation(BUTTERFLY_SpiritualStrengthRed);
			else if (1656 < getMidX() && getMidX() < 1671)
				setAnimation(BUTTERFLY_RestorePhysicalStrength);
			else if (1853 < getMidX() && getMidX() < 1868)
				setAnimation(BUTTERFLY_BonusBlue);
		}
	}
	else
	{
		setPhysicsEnable(true);
		if (abs(getMidX() - player->getMidX()) < 20 && isCollisionPlayer
			&& abs(getBottom() - player->getBottom()) < 5 && getRenderActive())
		{
			setRenderActive(false);
			isCollisionPlayer = false;

			switch (getAnimation())
			{
			case BUTTERFLY_SpiritualStrengthBlue:
				ScoreBar::getInstance()->increaseHeartCount(5);
				break;
			case BUTTERFLY_SpiritualStrengthRed:
				ScoreBar::getInstance()->increaseHeartCount(10);
				break;
			case BUTTERFLY_TimeFreeze:
				player->setFreezeTime(true);
				break;
			case BUTTERFLY_BonusRed:
				ScoreBar::getInstance()->increaseScore(1000);
				break;
			case BUTTERFLY_BonusBlue:
				ScoreBar::getInstance()->increaseScore(500);
				break;
			case BUTTERFLY_RestorePhysicalStrength:
				ScoreBar::getInstance()->restoreHealth();
				break;
			case BUTTERFLY_TheArtoftheFireWheel:
				ScoreBar::getInstance()->setWeapon(MISC_SPRITE_ID_FIRE_WHEEL);
				break;
			case BUTTERFLY_ThrowingStar:
				ScoreBar::getInstance()->setWeapon(MISC_SPRITE_ID_THROWING_STAR);
				player->setStarNormal(true);
				player->setStarWindmill(false);
				break;
			default:
				break;
			}
		}
		
	}
	
	PhysicsObject::onUpdate(dt);
}

void Butterfly::onCollision(MovableRect* other, float collisionTime, int nx, int ny)
{
	if (other->getCollisionType() == COLLISION_TYPE_GROUND)
	{
		preventMovementWhenCollision(collisionTime, nx, ny);
	}
	if (other->getCollisionType() == COLLISION_TYPE_PLAYER)
	{
		isCollisionPlayer = true;
	}
	PhysicsObject::onCollision(other, collisionTime, nx, ny);
}

Butterfly::Butterfly()
{
	setPhysicsEnable(false);
	setAnimation(BUTTERFLY_FLY);
	setDirection(TEXTURE_DIRECTION_LEFT);
	player = Player::getInstance();
	isCollisionPlayer = false;
}

Butterfly::~Butterfly()
{
}
