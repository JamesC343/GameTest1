#pragma once
#include "Surface.h"
#include "Entity.h"
#include <iostream>

class TerrainMap
{
public:
	TerrainMap(const Surface*);
	~TerrainMap();
	bool IsCollision(Vector<int>);
	//int GetMinYAtX(int);
	int GetYMove(Vector<int>);
private:
	bool ValidPosition(Vector<int>);

	int width;
	int height;
	//bool* terrainMatrix;
	int* terrainMatrix;
};

