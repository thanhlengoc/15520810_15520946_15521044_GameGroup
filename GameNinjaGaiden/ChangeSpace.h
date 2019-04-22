#pragma once
#include "Spaces.h"

class  ChangeSpace
{
public:
	virtual void setCurrentSpace(int spaceIndex) = 0;
	virtual Space* getCurrentSpace() = 0;
	virtual void resetLocationInSpace() = 0;
	virtual int getCurrentSpaceIndex() = 0;
};