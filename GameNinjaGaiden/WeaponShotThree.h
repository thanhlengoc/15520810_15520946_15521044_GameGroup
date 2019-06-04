#pragma once
#include "PhysicsObject.h"
#include"SpriteManager.h"
#include"Player.h"
#include"WeaponPlayer.h"

class WeaponShotThree :
	public PhysicsObject
{
	static WeaponShotThree* instance;

public:
	static WeaponShotThree* getInstance();
	WeaponPlayer* weapon_player;
	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
	WeaponShotThree();
	~WeaponShotThree();
};