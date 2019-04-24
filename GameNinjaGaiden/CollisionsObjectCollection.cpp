#include "CollisionsObjectCollection.h"



CollisionsObjectCollection * CollisionsObjectCollection::instance = 0;
CollisionsObjectCollection * CollisionsObjectCollection::getInstance()
{
	if (instance == 0)
		instance = new CollisionsObjectCollection();
	return instance;
}

CollisionsObjectCollection::CollisionsObjectCollection()
{
	collisionsObjectCollection = new List<BaseObject*>[COLLISION_TYPE_COUNT];
}


CollisionsObjectCollection::~CollisionsObjectCollection()
{
}

List<BaseObject*>* CollisionsObjectCollection::getCollection(COLLISION_TYPE collisionType)
{
	return &collisionsObjectCollection[collisionType];
}

void CollisionsObjectCollection::addObject(BaseObject * obj)
{
	getCollection(obj->getCollisionType())->_Add(obj);
	//getCollection(CT_ALL)->_Add(obj);
}

void CollisionsObjectCollection::removeObject(BaseObject * obj)
{
	for (size_t i = 0; i < COLLISION_TYPE_COUNT; i++)
	{
		getCollection((COLLISION_TYPE)i)->_Remove(obj);
	}
}

void CollisionsObjectCollection::clearAll()
{
	for (size_t i = 0; i < COLLISION_TYPE_COUNT; i++)
	{
		getCollection((COLLISION_TYPE)i)->Clear();
	}
}
