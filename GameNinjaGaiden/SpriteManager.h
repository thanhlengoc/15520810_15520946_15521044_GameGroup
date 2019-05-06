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

	SPRITE_COUNT
};

enum MISC_SPRITE_ID
{
	MISC_SPRITE_ID_NUMBER,
	MISC_SPRITE_ID_MORNING_STAR,
	MISC_SPRITE_ID_LOST_HEALTH,
	MISC_SPRITE_ID_KNIFE_ITEM,
	MISC_SPRITE_ID_TORCH,
	MISC_SPRITE_ID_EXPLOSION_EFFECT,
	MISC_SPRITE_ID_CANDLE,
	MISC_SPRITE_ID_MERMAN_BULLET,
	MISC_SPRITE_ID_ITEM_MORNING_STAR,
	MISC_SPRITE_ID_ITEM_SMALLHEART,
	MISC_SPRITE_ID_ITEM_WATER,
	MISC_SPRITE_ID_ITEM_BIGHEART,
	MISC_SPRITE_ID_ITEM_DAGGER,
	MISC_SPRITE_ID_ITEM_HOLYWATER,
	MISC_SPRITE_ID_ITEM_HOLYCROSS,
	MISC_SPRITE_ID_ITEM_AXE,
	MISC_SPRITE_ID_ITEM_GOLDPOTION,
	MISC_SPRITE_ID_ITEM_STOPWATCH,
	MISC_SPRITE_ID_ITEM_BREAK_WALL1,
	MISC_SPRITE_ID_ITEM_BREAK_WALL,
	MISC_SPRITE_ID_ITEM_400PTS,
	MISC_SPRITE_ID_ITEM_700PTS,
	MISC_SPRITE_ID_ITEM_1000PTS,
	MISC_SPRITE_ID_ITEM_BOOMERANG,
	MISC_SPRITE_ID_BOOMERANG,
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
