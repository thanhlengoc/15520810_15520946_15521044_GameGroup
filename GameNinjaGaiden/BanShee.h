#pragma once
#include "PhysicsObject.h"

enum {
	BANSHEE_WAIT,
	BANSHEE_RUN,
	BANSHEE_THROW
};
class BanShee:public PhysicsObject
{
public:
	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
	BanShee();
	~BanShee();
};