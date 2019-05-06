#include "Game.h"
#include "ScoreBar.h"

/* singleton pattern */
Game * Game::instance = 0;
Game * Game::getInstance()
{
	if (instance == 0)
		instance = new Game();
	return instance;
}

/* Các câu lệnh khởi tạo game */
void Game::GameInit()
{
	world = new World();

	world->Init("Image/Map/Map");
	Camera::getInstance()->setSize(
		GLOBALS_D("backbuffer_width"),
		GLOBALS_D("backbuffer_height"));


}
/* Các câu lệnh cập nhật game */
void Game::GameUpdate(float dt)
{
	world->update(dt);
	ScoreBar::getInstance()->update();
}
/* Các câu lệnh vẽ của game */
void Game::GameRender()
{
	world->render();
	//ScoreBar::getInstance()->render();
}

Game::Game()
{
}


Game::~Game()
{
}
