#pragma once
#include "PhysicsObject.h"
#include"SpriteManager.h"

enum {
	WEAPON_PLAYER_SWORD
};

class WeaponPlayer :
	public PhysicsObject
{
	static WeaponPlayer* instance;

public:
	static WeaponPlayer* getInstance();

	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
	WeaponPlayer();
	~WeaponPlayer();
};