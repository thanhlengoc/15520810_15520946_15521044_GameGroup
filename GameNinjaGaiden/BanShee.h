#pragma once
#include "PhysicsObject.h"
#include"Player.h"
#include"WeaponPlayer.h"
#include"WeaponThrow.h"
#include"WeaponStar.h"

enum BANSHEE_ACTION {
	BANSHEE_WAIT,
	BANSHEE_RUN,
	BANSHEE_THROW
};
class BanShee:public PhysicsObject
{
	int numberThrow;
	float vxThrow;
	float vyThrow;
	int directVx;

public:
	Player* player;
	WeaponPlayer* weapon_player;
	WeaponThrow* weapon_throw;
	WeaponStar* weapon_star;

	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
	void setFollowPlayer();
	BanShee();
	~BanShee();
};