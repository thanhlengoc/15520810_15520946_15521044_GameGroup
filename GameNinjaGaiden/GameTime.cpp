#include "GameTime.h"


GameTime::GameTime(void)
{
}

GameTime::GameTime(DWORD tickPerFrame)
{
	this->tickPerFrame = tickPerFrame;
}


bool GameTime::atTime()
{
	/* Lấy thời gian hiện tại */
	DWORD now = GetTickCount();
	/* Tính thời gian từ bây giờ tới lúc bắt đầu */
	deltaTime = now - startTime;
	/* Nếu khoảng thời gian đó lớn hơn thời gian cho trước */
	if (deltaTime >= tickPerFrame)
	{
		startTime = GetTickCount();
		/* Trả ra kết quả đúng */
		return true;
	}
	/* Chưa tới thời gian trả ra kết quả sai */
	return false;
}

GameTime::~GameTime(void)
{
}

DWORD GameTime::getStartTime()
{
	return startTime;
}
void GameTime::setStartTime(DWORD startTime)
{
	this->startTime = startTime;
}
DWORD GameTime::getTickPerFrame()
{
	return tickPerFrame;
}
void GameTime::setTickPerFrame(DWORD tickPerFrame)
{
	this->tickPerFrame = tickPerFrame;
}
void GameTime::init(DWORD tickPerFrame)
{
	setTickPerFrame(tickPerFrame);
}
DWORD GameTime::getDeltaTime()
{
	return deltaTime;
}
void GameTime::setDeltaTime(DWORD deltaTime)
{
	this->deltaTime = deltaTime;
}
