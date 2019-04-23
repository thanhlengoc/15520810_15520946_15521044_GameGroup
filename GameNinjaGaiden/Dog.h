#pragma once
#include "PhysicsObject.h"

enum {
	DOG_WAIT,
	DOG_RUN
};
class Dog:public PhysicsObject {
public:
	Dog();
	~Dog();
};