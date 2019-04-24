#pragma once
#include "PhysicsObject.h"
#include"Player.h"
#include"Slash.h"
#include"ResetEnemy.h"
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
	public PhysicsObject, public ResetEnemy
{
	SWORDMAN_STATE swordmanState;
	bool isDead;
	DelayTime deadTime;
	bool isOnAttack;
	bool isOnDistanceMove;
	bool isHurtPlayer;
	int tickTime;
	bool contactPlayer;

public:
	Player* player;
	bool onContactPlayer();
	void setContactPlayer(bool contactPlayer);
	void setSwordmanState(SWORDMAN_STATE swordmanState);
	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
	void setFollowPlayer();
	void resetLocationEmemy() override;

	SwordMan();
	~SwordMan();
};
