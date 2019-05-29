#include "Bird.h"

void Bird::onUpdate(float dt)
{
	PhysicsObject::onUpdate(dt);
}

void Bird::restoreLocation()
{
	BaseObject::restoreLocation();
}

void Bird::onCollision(MovableRect* other, float collisionTime, int nx, int ny)
{
	BaseObject::onCollision(other, collisionTime, nx, ny);
}

void Bird::setDirectDefault()
{
	if (getMidX() >= 205 && getMidX() <= 270)
	{
		setDirection(TEXTURE_DIRECTION_LEFT);
	}
	else
		if (getMidX() >= 892 && getMidX() <= 927)
		{
			setDirection(TEXTURE_DIRECTION_RIGHT);
		}
		else
			if (getMidX() >= 934 && getMidX() <= 959)
			{
				setDirection(TEXTURE_DIRECTION_LEFT);
			}
			else
				if (getMidX() >= 1248 && getMidX() <= 1315)
				{
					setDirection(TEXTURE_DIRECTION_RIGHT);
				}
				else
					if (getMidX() >= 5000 && getMidX() <= 5188)
					{
						setDirection(TEXTURE_DIRECTION_LEFT);
					}
					else
						if (getMidX() >= 5333 && getMidX() <= 5350)
						{
							setDirection(TEXTURE_DIRECTION_RIGHT);
						}
}

void Bird::setFollowPlayer()
{
	int distance = player->getMidX() - getMidX();
	if (distance < 0)
	{
		setDirection(TEXTURE_DIRECTION_RIGHT);
	}
	else
	{
		setDirection(TEXTURE_DIRECTION_LEFT);
	}
}

Bird::Bird()
{
	setPhysicsEnable(false);
	setAnimation(BIRD_WAIT);
}

Bird::~Bird()
{
}
