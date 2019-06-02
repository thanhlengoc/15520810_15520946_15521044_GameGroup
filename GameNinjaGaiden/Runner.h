#pragma once
#include"PhysicsObject.h"
#include"Player.h"
#include"WeaponPlayer.h"

enum {
	RUNNER_WAIT,
	RUNNER_RUN
};
class Runner
	: public PhysicsObject
{

public:
	WeaponPlayer* weapon_player;
	Player* player;
	void restoreLocation() override;
	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
	void setDirectDefault();

	Runner();
	~Runner();
};