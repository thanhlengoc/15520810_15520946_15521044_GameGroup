#pragma once
#include"PhysicsObject.h"
#include"Player.h"
#include"WeaponPlayer.h"

enum {
	BIRD_WAIT,
	BIRD_FLY
};
class Bird:public PhysicsObject
{
public:
	WeaponPlayer* weapon_player;
	Player* player;
	void onUpdate(float dt) override;
	void restoreLocation() override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
	void setDirectDefault();
	void setFollowPlayer();

};
