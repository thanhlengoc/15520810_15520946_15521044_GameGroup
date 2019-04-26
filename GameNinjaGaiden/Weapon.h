#pragma once
#pragma once
#include "PhysicsObject.h"
#include"SpriteManager.h"
#include"KEY.h"
#include"Player.h"

enum {
	WEAPON_SWORD
};

class Weapon :
	public PhysicsObject
{
	static Weapon* instance;
	bool isRender;
public:
	static Weapon* getInstance();

	bool isRenderWeapon();
	void setRenderWeapon(bool isRender);

	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
	Weapon();
	~Weapon();
};