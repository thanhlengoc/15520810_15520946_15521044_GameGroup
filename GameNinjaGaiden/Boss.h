#pragma once
#include"PhysicsObject.h"
#include"Player.h"

enum BOSS_ACTION {
	BOSS_STAND,
	BOSS_JUMP,
	BOSS_DIE
};
enum BOSS_STATE
{
	BOSS_STATE_WAIT,
	BOSS_STATE_JUMP,
	BOSS_STATE_INJURE,
	BOSS_STATE_DEAD
};
class Boss : public PhysicsObject
{
	BOSS_STATE bossState;
	bool isJump;
	int count;
public:
	Player* player;
	void setState(BOSS_STATE bossState);
	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
	void setFollowPlayer();

	Boss();
	~Boss();
};