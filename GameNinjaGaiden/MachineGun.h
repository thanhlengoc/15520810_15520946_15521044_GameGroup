#pragma once
#include"PhysicsObject.h"

enum {
	MACHINE_GUN_WAIT,
	MACHINE_GUN_RUN,
	MACHINE_GUN_ATTACK,
};
class Machine:public PhysicsObject
{
public:
	Machine();
	~Machine();
};
