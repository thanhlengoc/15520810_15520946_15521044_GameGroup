#pragma once
#include "PhysicsObject.h"

enum {
	BANSHEE_WAIT,
	BANSHEE_RUN,
	BANSHEE_ATTACK,
	BANSHEE_WEAPON_THROW
};
class BanShee:public PhysicsObject
{
public:
	BanShee();
	~BanShee();
};