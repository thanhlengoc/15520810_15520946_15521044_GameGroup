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
	void setFollowPlayer();

	Sparrow();
	~Sparrow();
};