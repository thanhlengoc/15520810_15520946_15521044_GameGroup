#pragma once
#include "MovableRect.h"
#define MAX(a,b) a>b? a:b
#define MIN(a,b) a>b? b:a
#include<iostream>
using namespace std;

class Collision
{
public:
	/* BroadphaseBox là khối chữ nhật bao quanh box và vector di chuyển của box */
	static MovableRect* GetSweptBroadPhaseBox(MovableRect* box);
	/* AABBCheck là kiểm tra 2 hình chữ nhật M và S có đang giao nhau hay không */
	static bool AABBCheck(Rect* M, Rect* S);
	/* Giá trị float trả ra là thời gian va chạm( < 1 thì chắc chắn có va chạm còn bằng 1 thì không có va chạm) */
	static float SweptAABB(MovableRect* M, MovableRect* S, float &normalX, float &normalY);
	/* phương thức kiểm tra và xử lý va chạm */
	static void CheckCollision(MovableRect* M, MovableRect* S);

	/* CONSTRUCTOR & DESTRUCTOR */
	Collision();
	~Collision();
};
