#pragma once
#pragma once
#include"List.h"
#include"CollisionType.h"
#include"BaseObject.h"

// danh sach cac mang cac object phan loai theo collisiontype. cac object nay hien tai dang o camera

class CollisionsObjectCollection
{
	List<BaseObject*>* collisionsObjectCollection;
	static CollisionsObjectCollection* instance;
public:
	static CollisionsObjectCollection* getInstance();
	CollisionsObjectCollection();
	~CollisionsObjectCollection();

	List<BaseObject*>* getCollection(COLLISION_TYPE collisionType);

	void addObject(BaseObject* obj);
	void removeObject(BaseObject* obj);

	void clearAll();
};

