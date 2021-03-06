#include"SpriteManager.h"
#include"DelayTime.h"
#include"Player.h"

struct SCORE_LOCATION
{
	int X;
	int Y;
	int MaxLength;
};

class ScoreBar 
{
	int weapon;
	Sprite* miscSprite;
	GameTexture* scoreBar;
	void renderNumber(int num, int x, int y, int maxLength);
	void renderHealth();
	void renderBossHealth();
	void renderWeapon();
	static ScoreBar* instance;
	SCORE_LOCATION lifeLocation;
	SCORE_LOCATION heartLocation;
	SCORE_LOCATION stageLocation;
	SCORE_LOCATION scoreLocation;
	SCORE_LOCATION timeLocation;
	SCORE_LOCATION healthLocation;
	SCORE_LOCATION subWeaponLocation;
	SCORE_LOCATION bossHealthLocation;

	int health;
	int bossHealth;
	int maxHealth;
	int playerLife;
	int heartCount;
	int currentStageNumber;
	int score;
	int time;
	DelayTime timeGame;
public:
	Player* player;
	static ScoreBar* getInstance();
	ScoreBar();
	~ScoreBar();
	void render();
	void update();

	void setWeapon(int weapon);

	void restoreHealth();
	void restoreBossHealth();

	int getPlayerLife();
	void setPlayerLife(int playerLife);
	void increasePlayerLife(int playerLife);

	int getHeartCount();
	void setHeartCount(int heartCount);
	void increaseHeartCount(int heartCount);

	int getScore();
	void setScore(int score);
	void increaseScore(int score);

	int getTime();
	void setTime(int time);
	void increaseTime(int time);

	int getHealth();
	void setHealth(int health);
	void increaseHealth(int health);
	void decreaseHealth(int health);

	int getBossHealth();
	void setBossHealth(int health);
	void increaseBossHealth(int health);

	int getMaxHealth();

	void setCurrentStageNumber(int currentStageNumber);
};