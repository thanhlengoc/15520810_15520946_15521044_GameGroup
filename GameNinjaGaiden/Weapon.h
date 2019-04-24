#pragma once
#pragma once
#include "PhysicsObject.h"
#include"SpriteManager.h"
#include"KEY.h"

enum {
	WEAPON_SWORD
};

class Weapon :
	public PhysicsObject
{
	static Weapon* instance;
public:
	static Weapon* getInstance();
	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
	Weapon();
	~Weapon();
};