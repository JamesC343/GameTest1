#pragma once

#include "PhysicalObject.h"

class TerrainObject : public PhysicalObject
{
public:
	TerrainObject(Sprite*, Vei2, Vei2);
	~TerrainObject();
};

