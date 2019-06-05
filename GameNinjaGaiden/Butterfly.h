#pragma once
#include"PhysicsObject.h"
#include"Player.h"

enum {
	BUTTERFLY_WAIT,
	BUTTERFLY_FLY,
	BUTTERFLY_SpiritualStrengthBlue,
	BUTTERFLY_SpiritualStrengthRed,
	BUTTERFLY_TimeFreeze,
	BUTTERFLY_ThrowingStar,
	BUTTERFLY_BonusRed,
	BUTTERFLY_BonusBlue,
	BUTTERFLY_RestorePhysicalStrength,
	BUTTERFLY_TheArtoftheFireWheel
};
class Butterfly: public PhysicsObject
{
	bool isCollisionPlayer;
public:
	Player* player;
	void setFollowPlayer();
	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;

	Butterfly();
	~Butterfly();
};