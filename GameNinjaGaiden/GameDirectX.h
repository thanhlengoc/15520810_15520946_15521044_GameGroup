#pragma once
#include<d3d9.h>
#include<d3dx9.h>
#include<Windows.h>
#include"GameConfiguration.h"
#include"WindowGame.h"

/* Hướng dẫn Xem hướng dẫn về directx phần này không quan trọng*/
class GameDirectX
{
private:
	LPDIRECT3DDEVICE9 d3ddv;// Cong cu load hinh ve hinh ve surface
	LPDIRECT3DSURFACE9 backBuffer;// Bo nho tam
	LPD3DXSPRITE sprite;
	HWND hWnd;
	static GameDirectX* instance;

	bool initDirectX();
	bool isInitSprite();
	bool isSetBackBuffer();
	void init();
	void error();

public:
	GameDirectX(void);
	~GameDirectX(void);
	static GameDirectX* getInstance();

	void Release();
	LPDIRECT3DDEVICE9 GetDevice();
	LPDIRECT3DSURFACE9 GetBackBuffer();
	LPD3DXSPRITE GetSprite();
	void PrintText(char* str, int size, int x, int y, DWORD color);
	void BeginGraphics();
	void EndGraphics();
	void PresentBackBuffer();
};
