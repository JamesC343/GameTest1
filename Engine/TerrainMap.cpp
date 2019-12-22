#include "TerrainMap.h"



TerrainMap::TerrainMap(const Surface* terrainFile)
	: width(terrainFile->GetWidth() * (10)), height(terrainFile->GetHeight() * (10))
{
	terrainMatrix = new int[width];
	int minY;

	for (int x = 0; x < terrainFile->GetWidth(); x++)
	{
		minY = 0;
		for (int y = 0; y < terrainFile->GetHeight() && minY == 0; y++)
			if (terrainFile->GetPixel(x, y) != Colors::Magenta)
				minY = y * (10);

		for (int a = 0; a < 10; a++)
			terrainMatrix[x * (10) + a] = minY;
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
	delete terrainMatrix;
}

bool TerrainMap::IsCollision(Vector<int> position)
{
	if (position.x < 0 || position.x >= width || position.y < 0 || position.y >= height)
		return false;

	if (terrainMatrix[position.x] > position.y)
		return false;

	return true;

	//return terrainMatrix[position.y * width + position.x];
}

//int TerrainMap::GetMinYAtX(int x)
//{
//	if (x < 0 || x >= width)
//		return 0;
//
//	for (int y = 0; y < height; y++)
//		if(terrainMatrix[y * width + x])
//			return y;
//}

int TerrainMap::GetYMove(Vector<int> position)
{
	if (!ValidPosition(position))
		return position.y;

	return terrainMatrix[position.x] - position.y;

	//if (IsCollision(position))
	//	for (int y = position.y; y >= 0; y--)
	//		if (!terrainMatrix[y * width + position.x])
	//			return y - position.y;

	//for (int y = position.y; y < height; y++)
	//	if (terrainMatrix[y * width + position.x])
	//		return y - 1 - position.y;

	//return 0;
}

bool TerrainMap::ValidPosition(Vector<int> position)
{
	if (position.x < 0 || position.x >= width || position.y < 0 || position.y >= height)
		return false;

	return true;
}
