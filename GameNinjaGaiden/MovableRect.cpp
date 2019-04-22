#include "MovableRect.h"

int abs(int a)
{
	if (a > 0)
		return a;
	return -a;
}

MovableRect::MovableRect()
{
	dx = 0;
	dy = 0;
}

COLLISION_TYPE MovableRect::getCollisionType()
{
	return collisionType;
}

void MovableRect::setCollisionType(COLLISION_TYPE collisionType)
{
	this->collisionType = collisionType;
}

void MovableRect::setDx(float dx)
{
	this->dx = dx;
}
void MovableRect::setDy(float dy)
{
	this->dy = dy;
}
float MovableRect::getDx()
{
	return dx;
}
float MovableRect::getDy()
{
	return dy;
}

void MovableRect::setIsCollision(bool isCollision)
{
	this->isCollision = true;
}

float MovableRect::getNextFrameX()
{
	return getX() + dx;
}

float MovableRect::getNextFrameY()
{
	return getY() + dy;
}

void MovableRect::goX()
{
	Rect::moveX(dx);
}

void MovableRect::goY()
{
	Rect::moveY(dy);
}

void MovableRect::updateLocation()
{
	if (isCollision && !isChangeDxOrDy)
	{
		if (abs((int)getDx()) > abs((int)dy))
			setDy(0);
		else
			setDx(0);
	}

	setX((int)(getX() + getDx() + 0.5));
	setY((int)(getY() + getDy() + 0.5));
}

bool MovableRect::canCollision()
{
	return true;
}

void MovableRect::onIntersect(MovableRect * other)
{
}

void MovableRect::onCollision(MovableRect * other, float collisionTime, int nx, int ny)
{
}

void MovableRect::preventMovementWhenCollision(float collisionTime, int nx, int ny)
{
	setIsCollision(true);
	/* dời vật M về sát vật S */
	if (nx != 0)
	{
		isChangeDxOrDy = true;
		/* nếu vật va chạm theo phương x */
		setDx(collisionTime*getDx());
		return;
	}
	if (ny != 0)
	{
		isChangeDxOrDy = true;
		/* nếu vật va chạm theo phương y */
		setDy(collisionTime*getDy());
		return;
	}

}

void MovableRect::update()
{
	isCollision = false;
	isChangeDxOrDy = false;
}

MovableRect::~MovableRect()
{
}
