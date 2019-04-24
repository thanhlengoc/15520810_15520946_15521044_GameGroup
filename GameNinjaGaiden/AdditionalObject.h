#pragma once
#include "PhysicsObject.h"
#include"SpriteManager.h"
#include"List.h"
class AdditionalObject :
	public PhysicsObject
{
private:
	bool needDelete;
	static List<AdditionalObject*>* objects;
public:
	static List<AdditionalObject*>* getObjects();
	static void objectsUpdate();
	virtual void setNeedDelete(bool needDelete);
	void onUpdate(float dt);
	AdditionalObject();
	~AdditionalObject();
};

