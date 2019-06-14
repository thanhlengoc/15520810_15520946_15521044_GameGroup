#pragma once
#include "Camera.h"
#include <string>
using namespace std;
#include <vector>
#include"Cell.h"
#include"Camera.h"

class Grid
{
	static Grid* instance;
	vector<Cell> listCells;
public:
	static Grid* getInstance();
	Grid();
	void initGrid(string path, int worldHeight);
	void update(List<BaseObject*> allObjects, List<BaseObject*>& objectsInCamera);
	~Grid();
	void addListObjects(Cell Cell, List<BaseObject*> allObjects, List<BaseObject*>& objectsInCamera);
	void removeListObjects(Cell Cell, List<BaseObject*> allObjects, List<BaseObject*>& objectsInCamera);
	void resetLocationOfObjects(Cell Cell, List<BaseObject*> allObjects);
	void resetlistCells();
};

