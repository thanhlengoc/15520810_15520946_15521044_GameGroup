#pragma once
#include<Windows.h>
class KEY
{
public:
	bool
		isLeftDown,
		isRightDown,
		isUpDown,
		isDownDown,
		isJumpDown,
		isPreviousJumpDown,
		isJumpPress,
		isAttackPress,
		isAttackDown,
		isPreviousAttackDown,
		isSpace1Down,
		isSpace2Down,
		isSpace3Down;

	static KEY* instance;
	static KEY* getInstance();

	void update();

	KEY();
	~KEY();
};
