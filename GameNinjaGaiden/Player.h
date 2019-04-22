#pragma once
#include "PhysicsObject.h"
#include"SpriteManager.h"
#include"KEY.h"
#include"DelayTime.h"
#include"World.h"
#include"ChangeSpace.h"

enum PLAYER_ACTION
{
	PLAYER_ACTION_STAND,
	PLAYER_ACTION_RUN,
	PLAYER_ACTION_JUMP,
	PLAYER_ACTION_JUMP_ATTACK,
	PLAYER_ACTION_ATTACK,
	PLAYER_ACTION_DEFENCE,
	PLAYER_ACTION_SIT,
	PLAYER_ACTION_SIT_ATTACK,
	PLAYER_ACTION_CLIMB,
	PLAYER_ACTION_DIE
};

class Player :
	public PhysicsObject
{
	static Player* instance;
	KEY* key;
	bool isOnAttack;

	DelayTime deadDelay;
public:
	static Player* getInstance();
	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;

	void startDeadDelay();
	bool isDead;
	void setIsOnAttack(bool isOnAttack);
	bool isAttack();

	ChangeSpace* changeSpace;

	Player();
	~Player();
};
