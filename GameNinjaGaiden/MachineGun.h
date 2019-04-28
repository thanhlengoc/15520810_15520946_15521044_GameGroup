#pragma once
#include"PhysicsObject.h"
#include"Player.h"
#include"WeaponPlayer.h"
#include"WeaponShot.h"

enum MACHINE_GUN_ACTION{
	MACHINE_GUN_WAIT,
	MACHINE_GUN_RUN,
	MACHINE_GUN_SHOT
};
class Machine
	:public PhysicsObject
{
	bool isDead;
	bool isShot;
	bool isRun;
	int numberShot;
	int numberRun;

public:
	Player* player;
	WeaponPlayer* weapon_player;
	WeaponShot* weapon_shot;
	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
	void setFollowPlayer();

	Machine();
	~Machine();
};
