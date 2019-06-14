#pragma once
/* sử dụng list */
#include"List.h"
#include"Sprite.h"

/* khai báo 1 define viết tắt cho chữ SpriteManager::getSprite */
#define SPR SpriteManager::getSprite

/* ta tạo 1 sprite info để lưu thông tin của các sprite */
enum SPRITE_INFO
{
	/* đối tượng không có hình ảnh ta sẽ đặt số âm */
	SPRITE_INFO_WOOD_BAR = -7,
	SPRITE_INFO_LADDER = -6,
	SPRITE_INFO_CLIFF = -5,
	SPRITE_INFO_WATER_SURFACE = -4,
	SPRITE_INFO_GATE = -3,
	SPRITE_INFO_WATER = -2,
	SPRITE_INFO_GROUND = -1,
	/* đối tượng có hình ảnh ta sẽ đặt số dương */
	SPRITE_INFO_RYU = 0,
	// thêm các sprite_info khác ở đây
	SPRITE_INFO_SWORDMAN = 1,
	SPRITE_INFO_DOG = 2,
	SPRITE_INFO_BUTTERFLY = 3,
	SPRITE_INFO_BIRD = 4,
	SPRITE_INFO_BAT = 5,
	SPRITE_INFO_BANSHEE = 6,
	SPRITE_INFO_MACHINE_GUN = 7,
	SPRITE_INFO_WEAPON_PLAYER = 8,
	SPRITE_INFO_WEAPON_SHOT = 9,
	SPRITE_INFO_WEAPON_THROW = 10,
	RYU_MISC=11,
	SPRITE_INFO_RUNNER = 12,
	SPRITE_INFO_GUNNER = 13,
	SPRITE_INFO_SPARROW = 14,
	SPRITE_INFO_BOSS = 15,
	SPRITE_INFO_BOSS_WEAPON = 16,
	SPRITE_INFO_OTHER_SHOT = 17,
	SPRITE_INFO_WEAPON_STAR = 18,

	SPRITE_COUNT
};

enum MISC_SPRITE_ID
{
	MISC_SPRITE_ID_NUMBER,
	MISC_SPRITE_ID_LOST_HEALTH,
	MISC_SPRITE_ID_FIRE_WHEEL,
	MISC_SPRITE_ID_THROWING_STAR,
	MISC_SPRITE_ID_WINDMILL_THROWING_STAR
};

class SpriteManager
{
	/* ta lưu tất cả sprite ở đây */
	List<Sprite*> sprites;

	/* singleton pattern */
	static SpriteManager* instance;
public:
	static SpriteManager* getInstance();

	/* dùng để lấy sprite từ spriteManager */
	static Sprite* getSprite(int spriteInfo);

	SpriteManager();
	~SpriteManager();
};
