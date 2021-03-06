#pragma once
#include "PhysicsObject.h"
#include"Player.h"
#include"WeaponPlayer.h"

enum {
	BAT_WAIT,
	BAT_FLY
};
class Bat:public PhysicsObject
{
public:
	Player* player;
	WeaponPlayer* weapon_player;
	Camera* camera;
	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
	void setFollowPlayer();
	Bat();
	~Bat();
};