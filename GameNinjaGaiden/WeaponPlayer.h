#pragma once
#include "PhysicsObject.h"
#include"SpriteManager.h"
#include"DelayTime.h"

enum {
	WEAPON_PLAYER_SWORD,
};

class WeaponPlayer :
	public PhysicsObject
{
	static WeaponPlayer* instance;
	DelayTime endAnimation;

public:
	static WeaponPlayer* getInstance();

	void startAnimationWeapon();
	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
	WeaponPlayer();
	~WeaponPlayer();
};