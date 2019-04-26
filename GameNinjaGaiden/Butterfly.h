#pragma once
#include"PhysicsObject.h"

enum {
	BUTTERFLY_WAIT,
	BUTTERFLY_FLY
};
class Butterfly: public PhysicsObject
{

public:
	void onUpdate(float dt) override;

	Butterfly();
	~Butterfly();
};