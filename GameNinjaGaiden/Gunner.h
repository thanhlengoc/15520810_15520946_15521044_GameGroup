#pragma once
#include"PhysicsObject.h"
#include"Player.h"
#include"WeaponPlayer.h"

enum GUNNER_ACTION {
	GUNNER_WAIT,
	GUNNER_GUN
};
class Gunner
	: public PhysicsObject
{

	bool isDead;
	bool isShot;
	int numberShot;

public:

	Player* player;
	WeaponPlayer* weapon_player;
	WeaponShot* weapon_shot;

	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
	void setFollowPlayer();

	Gunner();
	~Gunner();
};