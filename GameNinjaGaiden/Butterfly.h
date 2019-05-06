#pragma once
#include"PhysicsObject.h"
#include"Player.h"

enum {
	BUTTERFLY_WAIT,
	BUTTERFLY_FLY
};
class Butterfly: public PhysicsObject
{

public:
	Player* player;
	void onUpdate(float dt) override;

	Butterfly();
	~Butterfly();
};