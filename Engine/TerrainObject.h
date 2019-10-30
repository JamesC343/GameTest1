#pragma once

#include "PhysicalObject.h"

class TerrainObject : public PhysicalObject
{
public:
	TerrainObject(Sprite*, Vector<int>, Vector<int>, std::string);
	~TerrainObject();
private:
};

