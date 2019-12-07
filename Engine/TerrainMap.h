#pragma once
#include "Surface.h"
#include <iostream>

class TerrainMap
{
public:
	TerrainMap(const Surface*);
	~TerrainMap();
	bool IsCollision(Vector<int>);
	int GetMinYAtX(int);
	int GetWalkTarget(Vector<int>);
private:
	int width;
	int height;
	bool* terrainMatrix;
};

