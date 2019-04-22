#pragma once
#include"PhysicsObject.h"
#include"SpriteManager.h"

enum {
	SPLASH_SHOW
};

class SlashEffect : public PhysicsObject
{
	static SlashEffect* instance;
public:
	static SlashEffect* getInstance();
	void onUpdate(float dt) override;
	SlashEffect();
	~SlashEffect();
};