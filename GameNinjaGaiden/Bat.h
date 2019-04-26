#pragma once
#include "PhysicsObject.h"
enum {
	BAT_WAIT,
	BAT_FLY
};
class Bat:public PhysicsObject
{
public:
	void onUpdate(float dt) override;
	Bat();
	~Bat();
};