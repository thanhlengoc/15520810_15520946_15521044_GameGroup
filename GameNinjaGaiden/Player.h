#pragma once
#include "PhysicsObject.h"
#include"SpriteManager.h"
#include"KEY.h"
#include"DelayTime.h"
#include"World.h"
#include"ChangeSpace.h"
#include"WeaponStar.h"

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
	PLAYER_ACTION_CLIMB_WAIT,
	PLAYER_ACTION_CLIMB,
	PLAYER_ACTION_DIE,
	PLAYER_ACTION_HURT,
	PLAYER_ACTION_RESET
};

class Player :
	public PhysicsObject
{
	static Player* instance;
	WeaponStar* weaponStar;
	KEY* key;
	bool isOnAttack;
	bool decreaseHeal;
	bool lostHeal;
	bool restartTime;
	bool isFreezeTime;
	bool isStartFreezeTime;
	bool isOnThrowing;
	bool isStarNormal;
	bool isStarWindmill;

	DelayTime deadDelay;
	DelayTime hurtDelay;
	DelayTime freezeTimeDelay;

public:
	static Player* getInstance();
	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;

	bool isHurtRight;
	bool isHurtLeft;
	bool isDead;
	bool endDeadTime;
	void startDeadTime();

	void setFreezeTime(bool isFreezeTime);
	bool getFreezeTime();

	void setStarNormal(bool isStarNormal);
	bool getStarNormal();

	void setStarWindmill(bool isStarWindmill);
	bool getStarWindmill();

	void setIsOnAttack(bool isOnAttack);
	bool isAttack();

	int getSpacePlayer();

	ChangeSpace* changeSpace;

	Player();
	~Player();
};
