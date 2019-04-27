#pragma once
#include "PhysicsObject.h"
#include"Player.h"
#include"Weapon.h"

enum SWORDMAN_STATE {
	SWORDMAN_STATE_WAIT,
	SWORDMAN_STATE_RUN,
	SWORDMAN_STATE_DIE,
};
enum SWORDMAN_ACTION
{
	SWORDMAN_ACTION_STAND,
	SWORDMAN_ACTION_RUN_ATTACK,
	SWORDMAN_ACTION_DIE,
};
class SwordMan :
	public PhysicsObject
{
	bool isDead;

public:
	Player* player;
	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
	void setFollowPlayer();

	SwordMan();
	~SwordMan();
};
