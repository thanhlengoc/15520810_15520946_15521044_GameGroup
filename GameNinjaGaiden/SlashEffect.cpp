#include "SlashEffect.h"

SlashEffect * SlashEffect::instance = 0;

SlashEffect * SlashEffect::getInstance()
{
	if (instance == 0)
	{
		instance = new SlashEffect();
	}
	return instance;
}

void SlashEffect::onUpdate(float dt)
{

	setAnimation(SPLASH_SHOW);
}

SlashEffect::SlashEffect()
{
	setSprite(SPR(SPRITE_INFO_SLASH));
	setDirection(TEXTURE_DIRECTION_RIGHT);
	setAnimation(SPLASH_SHOW);
	setAlive(true);
}

SlashEffect::~SlashEffect()
{
}
