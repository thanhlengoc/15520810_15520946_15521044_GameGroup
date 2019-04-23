#pragma once
#include"PhysicsObject.h"

enum {
	BIRD_WAIT,
	BIRD_FLY
};
class Bird:public PhysicsObject
{
public:
	Bird();
	~Bird();
};
