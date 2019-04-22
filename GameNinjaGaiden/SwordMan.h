#pragma once
#include "PhysicsObject.h"
#include"Player.h"
#include"Slash.h"

enum SWORDMAN_STATE
{
	SWORDMAN_STATE_WAIT,
	SWORDMAN_STATE_RUN,
	SWORDMAN_STATE_ATTACK
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
	SWORDMAN_STATE swordmanState;
	bool isDead;
	DelayTime deadTime;
	bool isOnAttack;
	int tickTime;

public:
	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
	void setFollowPlayer();
	void restoreLocation() override;
	//ResetEnemyInWorld* resetEnemy;

	SwordMan();
	~SwordMan();
};
