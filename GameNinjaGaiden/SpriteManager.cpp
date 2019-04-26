#include "SpriteManager.h"
SpriteManager * SpriteManager::instance = 0;
SpriteManager * SpriteManager::getInstance()
{
	if (instance == 0)
	{
		instance = new SpriteManager();
	}
	return instance;
}
Sprite * SpriteManager::getSprite(int spriteInfo)
{
	return getInstance()->sprites[spriteInfo];
}
SpriteManager::SpriteManager()
{
	/* thêm SPRITE_COUNT phần tử cho list sprite */
	for (size_t i = 0; i < SPRITE_COUNT; i++)
	{
		sprites._Add(new Sprite());
	}
	/* thêm sprite ở đây */
	sprites[SPRITE_INFO_SWORDMAN]->InitFromFile("Image/Animation/swordman/out/image.png", "Image/Animation/swordman/out/swordman.info.dat");
	sprites[SPRITE_INFO_RYU]->InitFromFile("Image/Animation/ryu/out/image.png", "Image/Animation/ryu/out/ryu.info.dat");
	sprites[SPRITE_INFO_RYU]->image->direction = TEXTURE_DIRECTION_RIGHT;
	sprites[SPRITE_INFO_WEAPON]->InitFromFile("Image/Animation/weapon/out/image.png", "Image/Animation/weapon/out/weapon.info.dat");
	sprites[SPRITE_INFO_BUTTERFLY]->InitFromFile("Image/Animation/butterfly/out/image.png", "Image/Animation/butterfly/out/butterfly.info.dat");
	sprites[SPRITE_INFO_DOG]->InitFromFile("Image/Animation/dog/out/image.png", "Image/Animation/dog/out/dog.info.dat");
	sprites[SPRITE_INFO_BIRD]->InitFromFile("Image/Animation/bird/out/image.png", "Image/Animation/bird/out/bird.info.dat");
	sprites[SPRITE_INFO_BAT]->InitFromFile("Image/Animation/bat/out/image.png", "Image/Animation/bat/out/bat.info.dat");
	sprites[SPRITE_INFO_BANSHEE]->InitFromFile("Image/Animation/banshee/out/image.png", "Image/Animation/banshee/out/banshee.info.dat");
	sprites[SPRITE_INFO_MACHINE_GUN]->InitFromFile("Image/Animation/machine_gun/out/image.png", "Image/Animation/machine_gun/out/machine_gun.info.dat");

}
SpriteManager::~SpriteManager()
{
}
