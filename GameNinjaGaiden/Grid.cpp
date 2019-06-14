#include "Grid.h"
#include <fstream>
#include "Cell.h"
#include "Collision.h"
using namespace std;

Grid* Grid::instance = 0;
Grid* Grid::getInstance()
{
	if (instance == 0)
		instance = new Grid();
	return instance;
}
Grid::Grid()
{
}

void Grid::initGrid(string pathGrid, int worldHeight)
{
	int countCell;
	fstream fs(pathGrid);
	fs >> countCell;
	for (size_t i = 0; i < countCell; i++)
	{
		Cell cell;

		fs >> cell.Id >> cell.X >> cell.Y >> cell.numberofObjects;

		cell.Y = worldHeight - cell.Y;

		cell.rect.set(cell.X, cell.Y, GLOBALS_D("backbuffer_width") / 2, GLOBALS_D("backbuffer_height") / 2);

		if (cell.numberofObjects == 0)
		{
			listCells.push_back(cell);
			continue;
		}
		for (size_t j = 0; j < cell.numberofObjects; j++)
		{
			int idObject;
			fs >> idObject;
			cell.listObjects.push_back(idObject);
		}

		listCells.push_back(cell);
	}
}

void Grid::update(List<BaseObject*> allObjects, List<BaseObject*>& objectsInCamera)
{
	for (size_t i = 0; i < listCells.size(); i++)
	{
		bool IsIntersect = Collision::AABBCheck(&listCells[i].rect, Camera::getInstance());
		if (IsIntersect)
		{
			addListObjects(listCells[i], allObjects, objectsInCamera);
			listCells[i].isIntesected = true;
		}
		else if (listCells[i].isIntesected)
		{
			resetLocationOfObjects(listCells[i], allObjects);
			removeListObjects(listCells[i], allObjects, objectsInCamera);
			listCells[i].isIntesected = false;
		}
	}
}




Grid::~Grid()
{
}

void Grid::addListObjects(Cell Cell, List<BaseObject*> allObjects, List<BaseObject*>& objectsInCamera)
{
	for (size_t j = 0; j < Cell.listObjects.size(); j++)
	{
		auto idObject = Cell.listObjects[j];

		objectsInCamera._Add(allObjects.at(idObject));
	}
}

void Grid::removeListObjects(Cell Cell, List<BaseObject*> allObjects, List<BaseObject*>& objectsInCamera)
{
	for (size_t j = 0; j < Cell.listObjects.size(); j++)
	{
		auto idObject = Cell.listObjects[j];

		objectsInCamera._Remove(allObjects.at(idObject));
	}
}

void Grid::resetLocationOfObjects(Cell Cell, List<BaseObject*> allObjects)
{
	for (size_t j = 0; j < Cell.listObjects.size(); j++)
	{
		auto idObject = Cell.listObjects[j];
		allObjects.at(idObject)->restoreLocation();
		allObjects.at(idObject)->setAlive(true);
		if (allObjects.at(idObject)->getCollisionType() == COLLISION_TYPE_ENEMY)
			allObjects.at(idObject)->setRenderActive(true);
	}
}

void Grid::resetlistCells()
{
	listCells.clear();
}
