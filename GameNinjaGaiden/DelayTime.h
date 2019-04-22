#pragma once
#include<Windows.h>
//co tinh tam thoi
class DelayTime
{
private:
	DWORD startTime;
	DWORD tickPerFrame;
	bool ready, terminated;
public:
	// bat dau
	void start(DWORD time = -1);
	// khi thoi gian dinh san ket thuc
	bool isTerminated();
	void setIsTerminated(bool isTerminated);
	// trong thoi gian chay
	bool isOnTime();
	// goi trong object update
	void update();
	void init(DWORD time = -1);
	DelayTime();
	~DelayTime();
};

