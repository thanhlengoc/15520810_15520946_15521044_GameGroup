#pragma once
#include<Windows.h>
/* Frame bao gồm lớp RECT và anchor X và anchor Y */
class FrameAnimation : public RECT
{
public:
	int anchorX, anchorY;
};
