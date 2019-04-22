#pragma once
#include"MovableRect.h"
#include"Spaces.h"
/* camera là 1 hình chữ nhật có thể di chuyển nên sẽ kế thừa lại lớp MovableRect */
class Camera : public MovableRect
{
	static Camera* instance;
	Space* space;
public:
	bool preventMoving;
	static Camera* getInstance();
	/* phương thức chuyển đổi world qua view
		Tham số đầu vào là xWorld yWorld
	*/
	void convertWorldToView(float xWorld, float yWorld, float& xView, float& yView);
	void setSpace(Space* space);
	void update();
	Camera();
	~Camera();
};
