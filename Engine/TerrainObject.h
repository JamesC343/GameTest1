#pragma once

#include "PhysicalObject.h"

class TerrainObject : public PhysicalObject
{
public:
	TerrainObject(Sprite*, Vector<int> = { 0, 0 });
	~TerrainObject();
private:
};

