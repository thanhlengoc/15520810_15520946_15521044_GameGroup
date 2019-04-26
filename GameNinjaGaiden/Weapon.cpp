#include "Weapon.h"



Weapon * Weapon::instance = 0;
Weapon * Weapon::getInstance()
{
	if (instance == 0)
	{
		instance = new Weapon();
	}
	return instance;
}

bool Weapon::isRenderWeapon()
{
	return isRender;
}

void Weapon::setRenderWeapon(bool isRender)
{
	this->isRender = isRender;
}

void Weapon::onUpdate(float dt)
{
	Player* player = Player::getInstance();
	setInterval(200);
	if (getRenderActive())
	{
		setAnimation(WEAPON_SWORD);
		if (getIsLastFrameAnimationDone())
		{
			setRenderActive(false);
		}
		
	}
	PhysicsObject::onUpdate(dt);
}

void Weapon::onCollision(MovableRect * other, float collisionTime, int nx, int ny)
{
	PhysicsObject::onCollision(other, collisionTime, nx, ny);
}

Weapon::Weapon()
{
	setSprite(SPR(SPRITE_INFO_WEAPON));
	setCollisionType(COLLISION_TYPE_WEAPON);
	setRenderActive(false);
	setPhysicsEnable(false);
}


Weapon::~Weapon()
{
}
