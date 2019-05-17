#pragma once
#include"PhysicsObject.h"

enum {
	RUNNER_WAIT,
	RUNNER_RUN
};
class Runner
	: public PhysicsObject
{

public:
	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;

	Runner();
	~Runner();
};