#pragma once
enum COLLISION_TYPE
{
	COLLISION_TYPE_GROUND,
	COLLISION_TYPE_ENEMY,
	/* thêm các collisionType khác trong tool vào đây */
	COLLISION_TYPE_PLAYER,
	COLLISION_TYPE_WATER,
	COLLISION_TYPE_WEAPON,
	COLLISION_TYPE_GATE,
	
	/* số lượng collisionType luôn nằm cuối */
	COLLISION_TYPE_COUNT
};
