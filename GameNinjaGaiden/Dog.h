#pragma once
#include "PhysicsObject.h"

enum {
	DOG_WAIT,
	DOG_RUN
};
class Dog:public PhysicsObject {
public:

	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
	Dog();
	~Dog();
};