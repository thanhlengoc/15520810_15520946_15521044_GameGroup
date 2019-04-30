#include "WeaponPlayer.h"

WeaponPlayer * WeaponPlayer::instance = 0;
WeaponPlayer * WeaponPlayer::getInstance()
{
	if (instance == 0)
	{
		instance = new WeaponPlayer();
	}
	return instance;
}

void WeaponPlayer::startAnimationWeapon()
{
	endAnimation.start();
}

void WeaponPlayer::onUpdate(float dt)
{
	setInterval(200);
	if (getRenderActive())
	{
		setAnimation(WEAPON_PLAYER_SWORD);
		endAnimation.update();
		if (endAnimation.isTerminated())
		{
			setRenderActive(false);
		}
	}
	PhysicsObject::onUpdate(dt);
}

void WeaponPlayer::onCollision(MovableRect * other, float collisionTime, int nx, int ny)
{
	PhysicsObject::onCollision(other, collisionTime, nx, ny);
}

WeaponPlayer::WeaponPlayer()
{
	setSprite(SPR(SPRITE_INFO_WEAPON_PLAYER));
	setCollisionType(COLLISION_TYPE_WEAPON_PLAYER);
	setRenderActive(false);
	setPhysicsEnable(false);
	endAnimation.init(200);
}


WeaponPlayer::~WeaponPlayer()
{
}
