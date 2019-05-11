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
	Player* player = Player::getInstance();
	player->changeSpace = dynamic_cast<ChangeSpace*>(this);

	world = new World();
	world->changeSpace = dynamic_cast<ChangeSpace*>(this);

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
	if (getCurrentSpaceIndex() != 1 && getCurrentSpaceIndex() != 3 && getCurrentSpaceIndex() != 4)
		ScoreBar::getInstance()->render();
}

void Game::setCurrentSpace(int spaceIndex)
{
	world->currentSpaceIndex = spaceIndex;
	world->currentSpace = world->spaces.at(spaceIndex);
	Camera::getInstance()->setSpace(world->currentSpace);
}

Space * Game::getCurrentSpace()
{
	return world->currentSpace;
}

int Game::getCurrentSpaceIndex()
{
	return world->currentSpaceIndex;
}

void Game::resetLocationInSpace()
{
	Camera* camera = Camera::getInstance();
	Player* player = Player::getInstance();

	camera->setLocation(getCurrentSpace()->CameraX, getCurrentSpace()->CameraY);
	player->setLocation(getCurrentSpace()->PlayerX, getCurrentSpace()->PlayerY);

	ScoreBar::getInstance()->setTime(150);
}

Game::Game()
{
}


Game::~Game()
{
}
