#pragma once
#include "PhysicsObject.h"
#include"Player.h"

class Enemy :
	public PhysicsObject
{
	int health;
public:

	void setHealth(int health);
	int getHealth();
	void onInitFromFile(ifstream& fs, int mapHeight) override{}
	void setDirectionFollowPlayer();
	virtual void onDeath();
	virtual void onDecreaseHealth();
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny);
	void onIntersect(MovableRect* other) override;
	void restoreLocation() override;
	virtual void onContactPlayer();
	virtual void onContactWeapon();
	virtual bool canAttackPlayer();
	Enemy();
	~Enemy();
};

