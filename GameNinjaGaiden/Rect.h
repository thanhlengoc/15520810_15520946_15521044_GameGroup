#pragma once
class Rect
{
	/* x y width height của đối tượng */
	float x, y, width, height;
public:
	/* di chuyển hình chữ nhật theo phương x 1 khoảng dx */
	void moveX(float dx);
	/* di chuyển hình chữ nhật theo phương y 1 khoảng dy */
	void moveY(float dy);
	/* di chuyển hình chữ nhật theo 2 phương */
	void move(float dx, float dy);
	/* get set phương thức */
	float getX();
	float getY();
	float getWidth();
	float getHeight();
	virtual void setX(float x);
	virtual void setY(float y);
	virtual void setWidth(float width);
	virtual void setHeight(float height);
	void setLocation(float x, float y);
	void setSize(float width, float height);
	void set(float x, float y, float width, float height);
	/* lấy ra các phương left right top bottom của hình chữ nhật xem phương thức định nghĩa
	bên Rect.cpp sẽ hiểu */
	float getleft();
	float getRight();
	float getTop();
	float getBottom();
	/* vị trí giữa của rect */
	float getMidX();
	float getMidY();
	Rect();
	virtual ~Rect();
};
