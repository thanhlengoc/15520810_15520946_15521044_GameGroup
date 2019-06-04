#pragma once
#include"PhysicsObject.h"
#include"Player.h"
#include"WeaponPlayer.h"
#include"WeaponShot.h"
#include"WeaponShotSecond.h"
#include"WeaponShotThree.h"

enum MACHINE_GUN_ACTION{
	MACHINE_GUN_WAIT,
	MACHINE_GUN_RUN,
	MACHINE_GUN_SHOT
};
class Machine
	:public PhysicsObject
{
	//bool isDead;
	bool isShot;
	//bool isRun;
	int numberShot;
	int numberRun;

public:
	Player* player;
	WeaponPlayer* weapon_player;
	WeaponShot* weapon_shot;
	WeaponShotSecond* weapon_shot_second;
	WeaponShotThree* weapon_shot_three;
	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
	void setFollowPlayer();

	Machine();
	~Machine();
};
