#pragma once
#include "Rect.h"
#include"CollisionType.h"
/* đây là lớp Rect có thể di chuyển */
class MovableRect :
	public Rect
{
	/* độ dời di chuyển của đối tượng */
	float dx, dy;
	bool isCollision;
	bool isChangeDxOrDy;
	COLLISION_TYPE collisionType;
public:
	COLLISION_TYPE getCollisionType();
	void setCollisionType(COLLISION_TYPE collisionType);

	virtual void setDx(float dx);
	virtual void setDy(float dy);
	float getDx();
	float getDy();

	void setIsCollision(bool isCollision);
	float getNextFrameX();
	float getNextFrameY();
	/* phương thức di chuyển */
	void goX();
	void goY();

	virtual void updateLocation();
	virtual bool canCollision();
	virtual void onIntersect(MovableRect* other);
	virtual void onCollision(MovableRect* other, float collisionTime, int nx, int ny);
	void preventMovementWhenCollision(float collisionTime, int nx, int ny);
	virtual void update();

	MovableRect();
	~MovableRect();
};
