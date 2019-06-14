#include "Sparrow.h"
#include"ScoreBar.h"

void Sparrow::onUpdate(float dt)
{
	if (player->endDeadTime)
	{
		restoreLocation();
		setRenderActive(true);
		setAnimation(SPARROW_FLY);
		setPhysicsEnable(false);
		PhysicsObject::onUpdate(dt);
		return;
	}

	setFollowPlayer();

	if (getAnimation() == SPARROW_WAIT || getAnimation() == SPARROW_FLY)
	{
		setPhysicsEnable(false);
		if (player->isDead || player->getFreezeTime())
			setAnimation(SPARROW_WAIT);
		else
			setAnimation(SPARROW_FLY);

		if (abs(getMidX() - player->getMidX()) < 25 && player->isAttack()
			&& abs(getMidY() - player->getMidY()) < 15)
		{
			if (2659 < getMidX() && getMidX() < 2675)
				setAnimation(SPARROW_SpiritualStrengthBlue);
			else if (2752 < getMidX() && getMidX() < 2768)
				setAnimation(SPARROW_SpiritualStrengthRed);
			else if (3008 < getMidX() && getMidX() < 3024)
				setAnimation(SPARROW_BonusBlue);
			else if (3312 < getMidX() && getMidX() < 3328)
				setAnimation(SPARROW_WindmillThrowingStar);
			else if (3345 < getMidX() && getMidX() < 3361)
				setAnimation(SPARROW_SpiritualStrengthRed);
			else if (3696 < getMidX() && getMidX() < 3712)
				setAnimation(SPARROW_BonusRed);
			else if (3808 < getMidX() && getMidX() < 3824)
				setAnimation(SPARROW_SpiritualStrengthBlue);
			else if (4133 < getMidX() && getMidX() < 4149)
				setAnimation(SPARROW_BonusBlue);
			else if (4399 < getMidX() && getMidX() < 4415)
				setAnimation(SPARROW_BonusRed);
			else if (4496 < getMidX() && getMidX() < 4512)
				setAnimation(SPARROW_SpiritualStrengthBlue);
			else if (4672 < getMidX() && getMidX() < 4688)
				setAnimation(SPARROW_SpiritualStrengthRed);
			else if (4816 < getMidX() && getMidX() < 4832)
				setAnimation(SPARROW_BonusBlue);
			else if (4924 < getMidX() && getMidX() < 4940)
				setAnimation(SPARROW_WindmillThrowingStar);
			else if (5136 < getMidX() && getMidX() < 5152)
				setAnimation(SPARROW_SpiritualStrengthRed);
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
			case SPARROW_SpiritualStrengthBlue:
				ScoreBar::getInstance()->increaseHeartCount(5);
				break;
			case SPARROW_SpiritualStrengthRed:
				ScoreBar::getInstance()->increaseHeartCount(10);
				break;
			case SPARROW_BonusRed:
				ScoreBar::getInstance()->increaseScore(1000);
				break;
			case SPARROW_BonusBlue:
				ScoreBar::getInstance()->increaseScore(500);
				break;
			case SPARROW_WindmillThrowingStar:
				ScoreBar::getInstance()->setWeapon(MISC_SPRITE_ID_WINDMILL_THROWING_STAR);
				player->setStarNormal(false);
				player->setStarWindmill(true);
				break;
			case SPARROW_TheArtoftheFireWheel:
				ScoreBar::getInstance()->setWeapon(MISC_SPRITE_ID_FIRE_WHEEL);
				break;
			default:
				break;
			}
		}
	}
	PhysicsObject::onUpdate(dt);
}

void Sparrow::setFollowPlayer()
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

void Sparrow::onCollision(MovableRect* other, float collisionTime, int nx, int ny)
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

Sparrow::Sparrow()
{
	setPhysicsEnable(false);
	setAnimation(SPARROW_FLY);
	setDirection(TEXTURE_DIRECTION_LEFT);
	player = Player::getInstance();
	isCollisionPlayer = false;
}

Sparrow::~Sparrow()
{
}
