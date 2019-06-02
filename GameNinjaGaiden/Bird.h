#pragma once
#include"PhysicsObject.h"
#include"Player.h"
#include"WeaponPlayer.h"

enum BIRD_STATE {
	BIRD_WAIT,
	BIRD_FLY,
	BIRD_FIRST_FLY,
	BIRD_SECOND_FLY,
	BIRD_FLY_DOWN_RIGHT,
	BIRD_FLY_DOWN_LEFT,
	BIRD_FLY_UP_RIGHT,
	BIRD_FLY_UP_LEFT
};
class Bird:public PhysicsObject
{
	BIRD_STATE birdState;
 public:
	WeaponPlayer* weapon_player;
	Player* player;
	void setState(BIRD_STATE birdState);
	void onUpdate(float dt) override;
	void restoreLocation() override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
	void setDirectDefault();
	void setFollowPlayer();

	Bird();
	~Bird();
};
