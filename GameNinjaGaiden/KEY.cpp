#include "KEY.h"

DWORD getKeyChar(char keyChar)
{
	return ((int)keyChar - 'a') + 0x41;
}

KEY * KEY::instance = 0;
KEY * KEY::getInstance()
{
	if (instance == 0)
		instance = new KEY();
	return instance;
}

void KEY::update()
{
	isUpDown = GetAsyncKeyState(VK_UP);
	isDownDown = GetAsyncKeyState(VK_DOWN);
	isLeftDown = GetAsyncKeyState(VK_LEFT);
	isRightDown = GetAsyncKeyState(VK_RIGHT);

	isJumpDown = GetAsyncKeyState(VK_SPACE) || GetAsyncKeyState(getKeyChar('x'));
	isJumpPress = isJumpDown && !isPreviousJumpDown;
	isPreviousJumpDown = isJumpDown;

	isPreviousAttackDown = isAttackDown;
	isAttackDown = GetAsyncKeyState(getKeyChar('z'));
	isAttackPress = (isAttackDown==true && isPreviousAttackDown==false);

	isSpace1Down = GetAsyncKeyState(getKeyChar('q'));
	isSpace2Down = GetAsyncKeyState(getKeyChar('w'));
	isSpace3Down = GetAsyncKeyState(getKeyChar('e'));
}

KEY::KEY()
{
	isPreviousAttackDown = false;
}


KEY::~KEY()
{
}
