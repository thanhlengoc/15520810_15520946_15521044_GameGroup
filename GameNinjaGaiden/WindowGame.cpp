#include "WindowGame.h"
WindowGame::WindowGame(void)
{
}
WindowGame::~WindowGame(void)
{
}
WindowGame* WindowGame::instance = 0;
WindowGame* WindowGame::getInstance()
{
	if (instance == 0)
		instance = new WindowGame();
	return instance;
}
/* Hướng dẫn đọc hướng dẫn về handle window. phần này không quan trọng*/
void WindowGame::initHandleWindows(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEXA wcex;
	ZeroMemory(&wcex, sizeof(wcex));

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszClassName = GLOBALS_S("window_class");
	RegisterClassExA(&wcex);
	HWND hWnd = CreateWindowA(GLOBALS_S("window_class"), GLOBALS_S("window_title"), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, GLOBALS_D("window_width"), GLOBALS_D("window_height"), 0, 0, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	this->hWnd = hWnd;
}

/* Hướng dẫn đọc hướng dẫn về handle window. phần này không quan trọng*/
HWND WindowGame::getHandleWindow()
{
	return hWnd;
}

/* Hướng dẫn đọc hướng dẫn về handle window. phần này không quan trọng*/
LRESULT WindowGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
