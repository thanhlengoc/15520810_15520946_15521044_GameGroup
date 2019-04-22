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
	//sprites[SPRITE_INFO_DOG]->InitFromFile("Image/Animation/dog/out/image.png", "Image/Animation/dog/out/dog.info.dat");
	//sprites[SPRITE_INFO_BUTTERFLY]->InitFromFile("Image/Animation/butterfly/out/image.png", "Image/Animation/butterfly/out/butterfly.info.dat");
	//sprites[SPRITE_INFO_EAGLE]->InitFromFile("Image/Animation/eagle/out/image.png", "Image/Animation/eagle/out/eagle.info.dat");

}
SpriteManager::~SpriteManager()
{
}
