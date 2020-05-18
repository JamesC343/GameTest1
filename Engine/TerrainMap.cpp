#include "TerrainMap.h"



TerrainMap::TerrainMap(const Surface* terrainFile)
	: terrainSurface(terrainFile), size({ terrainFile->GetWidth(), terrainFile->GetHeight() })
{
	minY = new int[size.x];
	int tempY;

	for (int x = 0; x < terrainFile->GetWidth(); x++)
	{
		tempY = 0;
		for (int y = 0; y < terrainFile->GetHeight() && tempY == 0; y++)
			if (terrainFile->GetPixel(x, y) != Colors::Magenta)
				tempY = y;

		minY[x] = tempY;
	}


	//terrainMatrix = new bool[width * height];

	//for (int x = 0; x < terrainFile->GetWidth(); x++)
	//	for (int y = 0; y < terrainFile->GetHeight(); y++)
	//	{
	//		bool collide = terrainFile->GetPixel(x, y) == Colors::Magenta ? false : true;
	//		for (int a = 0; a < 10; a++)
	//			for (int b = 0; b < 10; b++)
	//				terrainMatrix[(y * (10) + b) * width + x * (10) + a] = collide;
	//	}

	//terrainMatrix = new bool[width * height];

	//for (int x = 0; x < width; x++)
	//	for (int y = 0; y < height; y++)
	//		terrainMatrix[y * width + x] = (terrainFile->GetPixel(x / (10), y / (10)) == Colors::Magenta) ? false : true;
}


TerrainMap::~TerrainMap()
{
	delete minY;
}

const Surface * TerrainMap::GetSurface()
{
	return terrainSurface;
}

bool TerrainMap::IsCollision(Vector<int> position)
{
	if (position.x < 0 || position.x >= size.x || position.y < 0 || position.y >= size.y)
		return false;

	if (minY[position.x] > position.y)
		return false;

	return true;
}

int TerrainMap::GetY(int xPosition)
{
	return minY[xPosition];
}

bool TerrainMap::ValidPosition(Vector<int> position)
{
	if (position.x < 0 || position.x >= size.x || position.y < 0 || position.y >= size.y)
		return false;

	return true;
}
