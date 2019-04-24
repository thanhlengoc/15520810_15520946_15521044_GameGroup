#include "AdditionalObject.h"
#include "Camera.h"
#include "Collision.h"
#include "CollisionsObjectCollection.h"

List<AdditionalObject*>* AdditionalObject::objects = 0;
List<AdditionalObject*>* AdditionalObject::getObjects()
{
	if (objects == 0)
		objects = new List<AdditionalObject*>();
	return objects;
}

void AdditionalObject::objectsUpdate()
{
	for (size_t i = 0; i < getObjects()->Count; i++)
	{
		auto o = objects->at(i);
		//o->performUpdate();
		if (o->needDelete)
		{
			objects->_Remove(o);
			CollisionsObjectCollection::getInstance()->removeObject(o);
			delete o;
			i--;
		}
	}
	for (size_t i = 0; i < getObjects()->Count; i++)
	{
		auto o = objects->at(i);
		CollisionsObjectCollection::getInstance()->addObject(o);
	}
}

void AdditionalObject::setNeedDelete(bool needDelete)
{
	this->needDelete = needDelete;
}


void AdditionalObject::onUpdate(float dt)
{
	if (!Collision::AABBCheck(this, Camera::getInstance()))
	{
		setNeedDelete(true);
	}
	PhysicsObject::onUpdate(dt);
}

AdditionalObject::AdditionalObject()
{
	getObjects()->_Add(this);
	setNeedDelete(false);
}


AdditionalObject::~AdditionalObject()
{
}
