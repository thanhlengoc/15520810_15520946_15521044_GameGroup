#pragma once
#include"PhysicsObject.h"
#include"SpriteManager.h"

enum {
	SLASH_SHOW
};
class  Slash: public PhysicsObject
{
	static Slash* instance;
public:

	static Slash* getInstance();
	void onUpdate(float dt) override;
	
	Slash();
	~Slash();
};