#pragma once
#include "PhysicsObject.h"
#include"SpriteManager.h"
#include"Player.h"

enum {
	WEAPON_THROW
};

class WeaponThrow :
	public PhysicsObject
{
	static WeaponThrow* instance;

public:
	static WeaponThrow* getInstance();

	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
	WeaponThrow();
	~WeaponThrow();
};