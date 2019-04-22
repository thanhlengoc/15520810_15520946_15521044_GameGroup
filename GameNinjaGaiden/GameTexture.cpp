#include "GameTexture.h"

GameTexture::GameTexture(const char* filepath, D3DCOLOR transColor)
{
	Init(filepath, transColor);
}

void GameTexture::Init(const char* filepath, D3DCOLOR transColor)
{
	direction = TEXTURE_DIRECTION_LEFT;
	HRESULT result;
	D3DXIMAGE_INFO info;
	result = D3DXGetImageInfoFromFileA(filepath, &info);
	Width = info.Width;
	Height = info.Height;
	if (result != D3D_OK)
		return;
	result = D3DXCreateTextureFromFileExA(
		GameDirectX::getInstance()->GetDevice(),
		filepath,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		transColor,
		&info,
		NULL,
		&m_image);

	if (result != D3D_OK)
		return;
}

void GameTexture::Render(int x, int y, int anchorX, int anchorY, RECT *r)
{
	GameDirectX::getInstance()->GetSprite()->Draw(m_image,
		r,
		&D3DXVECTOR3(anchorX, anchorY, 0),
		&D3DXVECTOR3(x, y, 0),
		D3DCOLOR_XRGB(255, 255, 255));
}

GameTexture::~GameTexture()
{
	if (m_image)
	{
		m_image->Release();
		m_image = 0;
	}

}
