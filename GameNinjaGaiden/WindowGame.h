#pragma once
#include<Windows.h>
#include"GameConfiguration.h"
class WindowGame
{
	/* Hướng dẫn đọc hướng dẫn về handle window. phần này không quan trọng*/
	HWND hWnd;
	/* Hướng dẫn Đọc hướng dẫn về singleton pattern */
	static WindowGame* instance;
public:
	/* Hướng dẫn Đọc hướng dẫn về singleton pattern */
	static WindowGame* getInstance();
	/* Hướng dẫn đọc hướng dẫn về handle window. phần này không quan trọng*/
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	/* Hướng dẫn đọc hướng dẫn về handle window. phần này không quan trọng*/
	void initHandleWindows(HINSTANCE hInstance, int nCmdShow);
	/* Hướng dẫn đọc hướng dẫn về handle window. phần này không quan trọng*/
	HWND getHandleWindow();
	WindowGame(void);
	~WindowGame(void);
};
