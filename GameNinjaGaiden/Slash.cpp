#include "Slash.h"

Slash * Slash::instance = 0;
Slash * Slash::getInstance()
{
	if (instance == 0)
	{
		instance = new Slash();
	}
	return instance;
}
void Slash::onUpdate(float dt)
{
	setAnimation(SLASH_SHOW);
}

Slash::Slash()
{
	setSprite(SPR(SPRITE_INFO_SLASH));
	setDirection(TEXTURE_DIRECTION_RIGHT);
	setAnimation(SLASH_SHOW);
	setAlive(true);
}

Slash::~Slash()
{
}
