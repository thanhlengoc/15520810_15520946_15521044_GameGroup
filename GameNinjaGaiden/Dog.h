#pragma once
#include "PhysicsObject.h"
#include"Player.h"

enum DOG_ACTION {
	DOG_WAIT,
	DOG_RUN
};
class Dog:
	public PhysicsObject {
public:

	Player* player;
	void onUpdate(float dt) override;
	void restoreLocation() override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
	void setDirectDefault();

	Dog();
	~Dog();
};