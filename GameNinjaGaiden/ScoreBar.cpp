#include "ScoreBar.h"
#include"Player.h"

#define NUMBER_WIDTH 8
#define HEALTH_WIDTH 4
void ignoreLineIfstream(ifstream& fs, int lineCount);


void ScoreBar::renderNumber(int num, int x, int y, int maxLength)
{
	int currentX = x + NUMBER_WIDTH * maxLength;
	int length = 0;
	while (num)
	{
		currentX -= NUMBER_WIDTH;
		int val = num % 10;
		miscSprite->render(currentX, y, MISC_SPRITE_ID_NUMBER, val);
		num /= 10;
		length++;
	}
	for (; length < maxLength; length++)
	{
		currentX -= NUMBER_WIDTH;
		miscSprite->render(currentX, y, MISC_SPRITE_ID_NUMBER, 0);
	}
}

void ScoreBar::renderHealth()
{
	int healthLost = maxHealth - health;
	int lastLocationXHealth = healthLocation.X + HEALTH_WIDTH * maxHealth - HEALTH_WIDTH;
	for (size_t i = 0; i < healthLost; i++)
	{
		miscSprite->render(lastLocationXHealth, healthLocation.Y, MISC_SPRITE_ID_LOST_HEALTH, 0);
		lastLocationXHealth -= HEALTH_WIDTH;
	}
}

void ScoreBar::renderBossHealth()
{
	int healthLost = maxHealth - bossHealth;
	if (healthLost > maxHealth)
	{
		healthLost = maxHealth;
	}
	int lastLocationXHealth = bossHealthLocation.X + HEALTH_WIDTH * maxHealth - HEALTH_WIDTH;
	for (size_t i = 0; i < healthLost; i++)
	{
		miscSprite->render(lastLocationXHealth, bossHealthLocation.Y, MISC_SPRITE_ID_LOST_HEALTH, 0);
		lastLocationXHealth -= HEALTH_WIDTH;
	}
}

/*
void ScoreBar::renderSubWeapon()
{
	if (this->subWeapon != 0)
	{
		this->subWeapon->getSprite()->render(subWeaponLocation.X,
			subWeaponLocation.Y,
			subWeapon->getAction(), 0);
	}
}
*/

ScoreBar * ScoreBar::instance = 0;
ScoreBar * ScoreBar::getInstance()
{
	if (instance == 0)
		instance = new ScoreBar();
	return instance;
}

ScoreBar::ScoreBar()
{
	scoreBar = new GameTexture("Image/ScoreBar/score_bar.png", D3DCOLOR_XRGB(10, 20, 60));
	miscSprite = SpriteManager::getInstance()->getSprite(RYU_MISC);
	timeGame.init(1000);
	timeGame.start();

	ifstream ifs("Image/ScoreBar/score_bar_item_location.dat");
	ignoreLineIfstream(ifs, 1);
	ifs >> lifeLocation.X >> lifeLocation.Y >> lifeLocation.MaxLength;
	setPlayerLife(2);
	setScore(0);

	ignoreLineIfstream(ifs, 2);
	ifs >> heartLocation.X >> heartLocation.Y >> heartLocation.MaxLength;
	setHeartCount(2);

	ignoreLineIfstream(ifs, 2);
	ifs >> stageLocation.X >> stageLocation.Y >> stageLocation.MaxLength;

	ignoreLineIfstream(ifs, 2);
	ifs >> scoreLocation.X >> scoreLocation.Y >> scoreLocation.MaxLength;

	ignoreLineIfstream(ifs, 2);
	ifs >> timeLocation.X >> timeLocation.Y >> timeLocation.MaxLength;

	ignoreLineIfstream(ifs, 2);
	ifs >> healthLocation.X >> healthLocation.Y >> maxHealth;

	ignoreLineIfstream(ifs, 2);
	ifs >> subWeaponLocation.X >> subWeaponLocation.Y;

	ignoreLineIfstream(ifs, 2);
	ifs >> bossHealthLocation.X >> bossHealthLocation.Y >> bossHealthLocation.MaxLength;

	setHealth(maxHealth);
	setBossHealth(maxHealth);
	setTime(150);
	setPlayerLife(2);
	setHeartCount(0);
	//setSubWeapon(0);
}


ScoreBar::~ScoreBar()
{
}

void ScoreBar::render()
{
	scoreBar->Render(0, 0, 0, 0, 0);
	renderNumber(getPlayerLife(), lifeLocation.X, lifeLocation.Y, lifeLocation.MaxLength);
	renderNumber(getHeartCount(), heartLocation.X, heartLocation.Y, heartLocation.MaxLength);
	renderNumber(currentStageNumber, stageLocation.X, stageLocation.Y, stageLocation.MaxLength);
	renderNumber(score, scoreLocation.X, scoreLocation.Y, scoreLocation.MaxLength);
	renderNumber(time, timeLocation.X, timeLocation.Y, timeLocation.MaxLength);
	renderHealth();
	renderBossHealth();
	//renderSubWeapon();
}


void ScoreBar::update()
{
	player = Player::getInstance();
	timeGame.update();
	if (timeGame.isTerminated())
	{
		timeGame.start();
		increaseTime(-1);
	}
}

/*
void ScoreBar::setSubWeapon(SubWeaponItem * subWeapon)
{
	this->subWeapon = subWeapon;
}
*/

void ScoreBar::restoreHealth()
{
	setHealth(maxHealth);
}

void ScoreBar::restoreBossHealth()
{
	setBossHealth(maxHealth);
}

int ScoreBar::getPlayerLife()
{
	return playerLife;
}

void ScoreBar::setPlayerLife(int playerLife)
{
	if (playerLife >= 0)
		this->playerLife = playerLife;
}

void ScoreBar::increasePlayerLife(int playerLife)
{
	setPlayerLife(this->playerLife + playerLife);
}

int ScoreBar::getHeartCount()
{
	return heartCount;
}

void ScoreBar::setHeartCount(int heartCount)
{
	this->heartCount = heartCount;
}

void ScoreBar::increaseHeartCount(int heartCount)
{
	setHeartCount(this->heartCount + heartCount);
}

void ScoreBar::setCurrentStageNumber(int currentStageNumber)
{
	this->currentStageNumber = currentStageNumber;
}

int ScoreBar::getScore()
{
	return score;
}
void ScoreBar::setScore(int score)
{
	this->score = score;
}
void ScoreBar::increaseScore(int score)
{
	this->score += score;
}

int ScoreBar::getTime()
{
	return time;
}
void ScoreBar::setTime(int time)
{
	if (time >= 0)
		this->time = time;
}
void ScoreBar::increaseTime(int time)
{
	setTime(this->time + time);
}

int ScoreBar::getHealth()
{
	return health;
}
void ScoreBar::setHealth(int health)
{
	if (health >= 0)
		this->health = health;
}
void ScoreBar::increaseHealth(int health)
{
	setHealth(this->health + health);
}

int ScoreBar::getBossHealth()
{
	return bossHealth;
}
void ScoreBar::setBossHealth(int health)
{
	this->bossHealth = health;
}
void ScoreBar::decreaseHealth(int health)
{
	if (this->health > 0)
		this->health -= health;
}
void ScoreBar::increaseBossHealth(int health)
{
	setBossHealth(bossHealth + health);
}

int ScoreBar::getMaxHealth()
{
	return maxHealth;
}
