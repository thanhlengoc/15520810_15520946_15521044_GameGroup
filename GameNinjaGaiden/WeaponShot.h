#pragma once
#include "PhysicsObject.h"
#include"SpriteManager.h"
#include"Player.h"
#include"WeaponPlayer.h"

enum {
	WEAPON_SHOT
};

class WeaponShot :
	public PhysicsObject
{
	static WeaponShot* instance;

public:
	static WeaponShot* getInstance();
	WeaponPlayer* weapon_player;
	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
	WeaponShot();
	~WeaponShot();
};