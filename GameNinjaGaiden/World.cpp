#include "World.h"
#include"Camera.h"
#include"KEY.h"
#include"SwordMan.h"
#include"Player.h"
#include"Collision.h"
#include"Dog.h"
#include"Butterfly.h"
#include"Bird.h"
#include"Bat.h"
#include"BanShee.h"
#include"MachineGun.h"
#include"Weapon.h"
#include"AdditionalObject.h"

void World::Init(const char * tilesheetPath, 
	const char * matrixPath, 
	const char * objectsPath,
	const char* collisionTypeCollidePath,
	const char* spacePath)
{
	Player* player = Player::getInstance();
	player->set(40, 70, 17, 32);

	Weapon* weapon = Weapon::getInstance();

	player->changeSpace = dynamic_cast<ChangeSpace*>(this);
	
	//Weapon* weapon = Weapon::getInstance();
	//weapon->set(40, 70, 17, 32);

	/* khởi tạo tilemap */
	tilemap.Init(tilesheetPath, matrixPath);

	int worldHeight = tilemap.getWorldHeight();

	for (size_t i = 0; i < COLLISION_TYPE_COUNT; i++)
	{
		objectCategories._Add(new List<BaseObject*>());
	}

	/* khởi tạo đối tượng */
	int objectCount;
	int collisionType, id, x, y, width, height;

	ifstream fs(objectsPath);
	fs >> objectCount;
	for (size_t i = 0; i < objectCount; i++)
	{
		BaseObject* obj;
		/* đọc id đối tượng */
		fs >> id;
		switch (id)
		{

		case SPRITE_INFO_SWORDMAN:
			obj = new SwordMan();
			break;
		case SPRITE_INFO_WEAPON:
			obj = new Weapon();
			break;
		/*
		case SPRITE_INFO_BUTTERFLY:
			obj = new Butterfly();
			break;
		case SPRITE_INFO_DOG:
			obj = new Dog();
			break;
		case SPRITE_INFO_BIRD:
			obj = new Bird();
			break;
		case SPRITE_INFO_BAT:
			obj = new Bat();
			break;
		case SPRITE_INFO_BANSHEE:
			obj = new BanShee();
			break;
		case SPRITE_INFO_MACHINE_GUN:
			obj = new Machine();
			break;
			*/

		default:
			obj = new BaseObject();
			break;
		}

		/* đọc thông số của đối tượng */
		obj->onInitFromFile(fs, worldHeight);
		if (id >= 0)
		{
			/* nếu id đối tượng không âm tức đối tượng có sprite ta gán sprite cho nó */
			obj->setSprite(SPR(id));
		}
		/* thêm đối tượng vào danh sách */
		allObjects._Add(obj);
		objectCategories.at(obj->getCollisionType())->_Add(obj);
	}

	int numberOfCollisionTypeCollides = 0;
	ifstream fsColli(collisionTypeCollidePath);
	fsColli >> numberOfCollisionTypeCollides;
	for (size_t i = 0; i < numberOfCollisionTypeCollides; i++)
	{
		int collisionType1, collisionType2;
		fsColli >> collisionType1 >> collisionType2;
		CollisionTypeCollide* collisionTypeCollide = new CollisionTypeCollide();
		collisionTypeCollide->COLLISION_TYPE_1 = (COLLISION_TYPE)collisionType1;
		collisionTypeCollide->COLLISION_TYPE_2 = (COLLISION_TYPE)collisionType2;
		collisionTypeCollides._Add(collisionTypeCollide);
	}

	/* đọc space */
	int numberOfSpaces = 0;
	ifstream fsSpace(spacePath);
	/* enter 1 dòng */
	ignoreLineIfstream(fsSpace, 1);
	fsSpace >> numberOfSpaces;
	for (size_t i = 0; i < numberOfSpaces; i++)
	{
		/* enter 4 dòng */
		ignoreLineIfstream(fsSpace, 4);
		Space* space = new Space();
		fsSpace >> space->X >> space->Y >> space->Width >> space->Height;

		/* enter 2 dòng */
		ignoreLineIfstream(fsSpace, 2);
		fsSpace >> space->CameraX >> space->CameraY;

		/* enter 2 dòng */
		ignoreLineIfstream(fsSpace, 2);
		fsSpace >> space->PlayerX >> space->PlayerY;

		/* do chiều y của trong file định nghĩa ngược với chiều logic nên cần đổi lại */
		space->CameraY = worldHeight - space->CameraY;
		space->PlayerY = worldHeight - space->PlayerY;
		space->Y = worldHeight - space->Y;

		/* thêm vào space */
		spaces._Add(space);
	}

	/* bắt đầu từ space 0 */
	setCurrentSpace(1);
	resetLocationInSpace();
}

void World::Init(const char * folderPath)
{
	/* tìm đường dẫn tilesheet và matrix object */
	string folderPathString = (string)folderPath;
	string tilesheetString = folderPathString;
	tilesheetString.append("/tilesheet.png");
	string matrixPathString = folderPathString;
	matrixPathString.append("/matrix.dat");
	string objectPathString = folderPathString;
	objectPathString.append("/objects.dat");
	string collisionTypeCollidePath = folderPathString;
	collisionTypeCollidePath.append("/collision_type_collides.dat");

	string spacePath = folderPathString;
	spacePath.append("/spaces.dat");


	Init(tilesheetString.c_str(),
		matrixPathString.c_str(),
		objectPathString.c_str(),
		collisionTypeCollidePath.c_str(),
		spacePath.c_str());
}

void World::update(float dt)
{
	KEY* key = KEY::getInstance();
	key->update();
	/* chuyển space khi nhấn phím */
	if (key->isJumpPress)
	{
		if (getCurrentSpaceIndex() == 1)
		{
			setCurrentSpace(0);
			resetLocationInSpace();
		}
		if (getCurrentSpaceIndex() == 3)
		{
			setCurrentSpace(2);
			resetLocationInSpace();
		}
		if (getCurrentSpaceIndex() == 3)
		{
			setCurrentSpace(2);
			resetLocationInSpace();
		}
		if (getCurrentSpaceIndex() == 4)
		{
			setCurrentSpace(5);
			resetLocationInSpace();
		}
	}

	if (key->isSpace1Down)
	{
		setCurrentSpace(0);
		resetLocationInSpace();
	}
	if (key->isSpace2Down)
	{
		setCurrentSpace(2);
		resetLocationInSpace();
	}
	if (key->isSpace3Down)
	{
		setCurrentSpace(5);
		resetLocationInSpace();
	}

	for (size_t i = 0; i < allObjects.Count; i++)
	{
		/* cập nhật đối tượng */
		allObjects[i]->update(dt);
		Collision::CheckCollision(Player::getInstance(), allObjects[i]);
		Collision::CheckCollision(Weapon::getInstance(), allObjects[i]);
	}
	/* xét va chạm cho các loại đối tượng với nhau */
	for (size_t i = 0; i < collisionTypeCollides.size(); i++)
	{
		COLLISION_TYPE col1 = collisionTypeCollides.at(i)->COLLISION_TYPE_1;
		COLLISION_TYPE col2 = collisionTypeCollides.at(i)->COLLISION_TYPE_2;

		/* danh sách đối tượng thuộc collision type 1 */
		List<BaseObject*>* collection1 = objectCategories.at(col1);
		/* danh sách đối tượng thuộc collision type 2 */
		List<BaseObject*>* collection2 = objectCategories.at(col2);

		for (size_t i1 = 0; i1 < collection1->size(); i1++)
		{
			for (size_t i2 = 0; i2 < collection2->size(); i2++)
			{
				/* cho xét va chạm của đối tượng dựa vào 1 cặp collisionType trong CollisionTypeCollide */
				Collision::CheckCollision(collection1->at(i1), collection2->at(i2));
			}
		}

	}
	//AdditionalObject::objectsUpdate();
	Weapon::getInstance()->update(dt);
	Player::getInstance()->update(dt);
	Camera::getInstance()->update();
}

void World::setCurrentSpace(int spaceIndex)
{
	currentSpaceIndex = spaceIndex;
	this->currentSpace = spaces.at(spaceIndex);
	Camera::getInstance()->setSpace(this->currentSpace);
}

Space * World::getCurrentSpace()
{
	return currentSpace;
}

int World::getCurrentSpaceIndex()
{
	return currentSpaceIndex;
}

void World::resetLocationInSpace()
{
	Camera* camera = Camera::getInstance();
	Player* player = Player::getInstance();

	camera->setLocation(getCurrentSpace()->CameraX, getCurrentSpace()->CameraY);
	player->setLocation(getCurrentSpace()->PlayerX, getCurrentSpace()->PlayerY);
}

void World::render()
{
	tilemap.render(Camera::getInstance());
	for (size_t i = 0; i < allObjects.Count; i++)
	{
		/* vẽ đối tượng */
		allObjects[i]->render(Camera::getInstance());
	}
	Player::getInstance()->render(Camera::getInstance());
	Weapon::getInstance()->render(Camera::getInstance());
}

World::World()
{
}
World::~World()
{
}
