#pragma once
#include"Animation.h"
#include"GameTexture.h"
#include"GameUtils.h"
class Sprite
{
public:
	/* Hình ảnh của đối tượng game */
	GameTexture* image;
	/* danh sách animation của đối tượng game */
	List<Animation*> animations;

	/* imagePath : đường dẫn hình
		infoPath : đường dẫn file cấu hình danh sách animation
	*/
	void InitFromFile(const char* imagePath, const char* infoPath);

	/* animationIndex: loại animation cần cập nhật
		frameIndex: frame cần cập nhật
	*/
	void update(int animationIndex, int& frameIndex);

	void render(int x, int y, int animationIndex, int frameIndex);
	int getFrameWidth(int animationIndex, int frameIndex);
	int getFrameHeight(int animationIndex, int frameIndex);

	Sprite();
	~Sprite();
};

