#pragma once
#include "PhysicsObject.h"
#include"SpriteManager.h"

enum
{
	WEAPON_STAR,
	WEAPON_WINDMILL_STAR
};
class WeaponStar :
	public PhysicsObject
{
	static WeaponStar* instance;

public:
	static WeaponStar* getInstance();
	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
	WeaponStar();
	~WeaponStar();
};