#pragma once
#include"PhysicsObject.h"

enum {
	MACHINE_GUN_WAIT,
	MACHINE_GUN_RUN,
	MACHINE_GUN_SHOT
};
class Machine
	:public PhysicsObject
{

public:

	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;

	Machine();
	~Machine();
};
