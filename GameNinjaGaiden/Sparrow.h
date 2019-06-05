#pragma once
#include"PhysicsObject.h"
#include"Player.h"

enum
{
	SPARROW_WAIT,
	SPARROW_FLY,
	SPARROW_SpiritualStrengthBlue,
	SPARROW_SpiritualStrengthRed,
	SPARROW_BonusBlue,
	SPARROW_WindmillThrowingStar,
	SPARROW_BonusRed,
	SPARROW_TheArtoftheFireWheel
};
class Sparrow 
	: public PhysicsObject 
{
	bool isCollisionPlayer;
public:
	Player* player;
	void onUpdate(float dt) override;
	void setFollowPlayer();
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;

	Sparrow();
	~Sparrow();
};