#include<Windows.h>
#include"WindowGame.h"
#include"GameDirectX.h"
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<fstream>
#include <iostream>
#include <chrono>
#include <thread>
#include"GameTexture.h"
#include"Game.h"
using namespace std;



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WindowGame::getInstance()->initHandleWindows(hInstance, nCmdShow);
	srand(time(NULL));

	/* GetTickCount: lấy thời gian hiện tại của hệ thống */
	/* Tính thời gian bắt đầu */
	DWORD startTime = GetTickCount();

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	/* Tính thời gian cho mỗi frame */
	DWORD timePerFrame = 1000 / GLOBALS_D("fps");

	Game::getInstance()->GameInit();

	/* vòng lặp game */
	while (msg.message != WM_QUIT)
	{
		/* now là thời gian hiện tại */
		DWORD now = GetTickCount();
		/* nếu khoảng thời gian kể từ lúc bắt đầu tới bây giờ lớn hơn thời gian cho mỗi frame thì khởi tạo lại thời gian bắt đầu
		là bây giờ*/
		DWORD deltaTime = now - startTime;
		if (deltaTime >= timePerFrame)
		{
			float time = deltaTime / 1000.0f;
			Game::getInstance()->GameUpdate(time);
			startTime = now;
			if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			GameDirectX::getInstance()->BeginGraphics();//bat dau ve len backbuffer
			Game::getInstance()->GameRender();
			GameDirectX::getInstance()->EndGraphics();// ket thuc ve len backbuffer
			GameDirectX::getInstance()->PresentBackBuffer();// ve backbuffer len man hinh
		}

	}
	return nCmdShow;
}
