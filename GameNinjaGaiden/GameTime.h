#pragma once
#include<Windows.h>
class GameTime
{
	/* Thời gian bắt đầu */
	DWORD startTime;
	/* Khoảng thời gian delay */
	DWORD tickPerFrame;
	/* Khoảng thời gian kể từ starttime tới bây giờ */
	DWORD deltaTime;
public:

	DWORD getStartTime();
	void setStartTime(DWORD startTime);
	DWORD getTickPerFrame();
	void setTickPerFrame(DWORD tickPerFrame);
	void init(DWORD tickPerFrame);
	DWORD getDeltaTime();
	void setDeltaTime(DWORD deltaTime);

	GameTime(void);
	~GameTime(void);

	GameTime(DWORD tickPerFrame);
	/* Tới thời gian hiện tại */
	virtual bool atTime();
};
