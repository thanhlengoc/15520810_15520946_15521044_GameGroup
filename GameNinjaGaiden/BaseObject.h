#pragma once
#include "MovableRect.h"
#include"Sprite.h"
#include"GameTime.h"
#include"Camera.h"

/* Đây là đối tượng của game. Kế thừa lại lớp đối tượng có thể chuyển động */
class BaseObject :
	public MovableRect
{
	Sprite* sprite;
	int animationIndex, frameIndex;

	int interval;
	int spriteId;
	/* dùng để làm chậm animation */
	GameTime animationGameTime;
	/* dừng animation */
	bool pauseAnimation;
	bool alive;
	// dung de restore location
	Rect* initBox;
	bool renderActive;
	bool isLastFrameAnimationDone;

	TEXTURE_DIRECTION direction;

public:
	void setSprite(Sprite*sprite);
	Sprite* getSprite();
	int getAnimation();
	void setAnimation(int animation);

	int getFrameAnimation();
	void setFrameAnimation(int frameAnimation);

	int getCurrentFrameWidth();
	int getCurrentFrameHeight();

	bool getPauseAnimation();
	virtual void setPauseAnimation(bool pauseAnimation);

	bool getIsLastFrameAnimationDone();
	virtual void setIsLastFrameAnimationDone(bool isLastFrameAnimationDone);

	/* hàm ảo được gọi khi khởi tạo đối tượng đọc từ file, mỗi đối tượng sẽ thực hiện phương thức này khác nhau */
	virtual void onInitFromFile(ifstream& fs, int mapHeight);

	/* hàm ảo, hành động update của đối tượng, do mỗi đối tượng có phương thức cập nhật khác nhau
		như con zombie thì chạy còn con dơi thì bay hình sin
	*/
	virtual void onUpdate(float dt);
	/* hành động cập nhật của đối tượng sau mỗi lần vẽ lại */

	void update(float dt);
	virtual void render(Camera* camera);

	TEXTURE_DIRECTION getDirection();
	void setDirection(TEXTURE_DIRECTION direction);

	Rect* getInitBox();
	void setInitBox(Rect* initBox);

	bool isAlive();
	virtual void setAlive(bool alive);

	bool canCollision();

	virtual bool canRemoveFromCamera();

	int distanceHorToFirstLocation();
	virtual void restoreLocation();

	// animation interval
	void setInterval(int interval);
	int getInterval();

	// active ve
	void setRenderActive(bool renderActive);
	bool getRenderActive();

	void onIntersect(MovableRect* other) override {}
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override {}

	BaseObject();
	~BaseObject();
};
