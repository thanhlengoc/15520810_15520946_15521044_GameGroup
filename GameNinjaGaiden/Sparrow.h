#pragma once
#include"PhysicsObject.h"
#include"Player.h"

enum
{
	SPARROW_WAIT,
	SPARROW_FLY
};
class Sparrow 
	: public PhysicsObject 
{

public:
	Player* player;
	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
	void setFollowPlayer();

	Sparrow();
	~Sparrow();
};