#pragma once
#include "PhysicsObject.h"
#include"SpriteManager.h"
#include"Player.h"
#include"WeaponPlayer.h"

class WeaponShotSecond :
	public PhysicsObject
{
	static WeaponShotSecond* instance;

public:
	static WeaponShotSecond* getInstance();
	WeaponPlayer* weapon_player;
	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
	WeaponShotSecond();
	~WeaponShotSecond();
};