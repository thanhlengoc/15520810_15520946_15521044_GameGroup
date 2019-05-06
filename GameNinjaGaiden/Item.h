#pragma once
#include"PhysicsObject.h"
#include"Player.h"

enum ITEM_ACTION
{

};

class Item
	:public PhysicsObject
{

public:
	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;

	Item();
	~Item();
};
