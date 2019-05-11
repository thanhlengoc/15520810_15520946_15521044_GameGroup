#pragma once
#include"Tilemap.h"
#include"SpriteManager.h"
#include"BaseObject.h"
#include"CollisionTypeCollide.h"
#include"Spaces.h"
#include"ChangeSpace.h"

class World
{
	/* dùng tilemap để vẽ map */
	Tilemap tilemap;

	/* tất cả object có trong world */
	List<BaseObject*> allObjects;

	List<CollisionTypeCollide*> collisionTypeCollides;
	List<List<BaseObject*>*> objectCategories;

public:
	void Init(const char* tilesheetPath,
		const char* matrixPath, 
		const char* objectsPath,
		const char* collisionTypeCollidePath,
		const char* spacePath);
	void Init(const char* folderPath);
	void update(float dt);

	List<Space*> spaces;
	Space* currentSpace;
	int currentSpaceIndex;

	ChangeSpace* changeSpace;
	/*
	void setCurrentSpace(int spaceIndex) override;
	Space* getCurrentSpace() override;
	int getCurrentSpaceIndex() override;
	void resetLocationInSpace() override;
	*/

	void render();
	World();
	~World();
};