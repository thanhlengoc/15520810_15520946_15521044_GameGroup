#include "Animation.h"
int Animation::NextFrame(int currentFrame)
{
	/* Ví dụ có 3 frame thì đảm bảo currentFrame chỉ trong 0 1 2 và không thể vượt quá 3 */
	if (currentFrame >= frames.size() - 1)
	{
		/* Nếu vượt quá thì quay lại frame đầu */
		return 0;
	}
	/* Nếu chưa tới 3 frame thì chuyển qua frame kế */
	return currentFrame + 1;
}
Animation::Animation()
{
}
Animation::~Animation()
{
}
