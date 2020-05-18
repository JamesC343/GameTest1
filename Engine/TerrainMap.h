#pragma once
#include "Surface.h"
#include "Entity.h"
#include <iostream>

class TerrainMap
{
public:
	TerrainMap(const Surface*);
	~TerrainMap();
	const Surface* GetSurface();
	bool IsCollision(Vector<int>);
	int GetY(int);
	bool ValidPosition(Vector<int> = { 0, 0 });
protected:
	const Surface* terrainSurface;
	Vector<int> size;
	int* minY;
};

