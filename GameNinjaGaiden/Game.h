#pragma once
#include"GameTexture.h"
#include"List.h"
#include"GameTime.h"
#include"FrameAnimation.h"
#include"Sprite.h"
#include"TileMap.h"
#include"World.h"
#include"Player.h"
#include"ChangeSpace.h"

class Game: public ChangeSpace
{
	/* singleton pattern */
	static Game* instance;
	World* world;

public:
	static Game* getInstance();

	/* Các câu lệnh khởi tạo game */
	void GameInit();
	/* Các câu lệnh cập nhật game */
	void GameUpdate(float dt);
	/* Các câu lệnh vẽ của game */
	void GameRender();

	void setCurrentSpace(int spaceIndex) override;
	Space* getCurrentSpace() override;
	int getCurrentSpaceIndex() override;
	void resetLocationInSpace() override;

	Game();
	~Game();
};
