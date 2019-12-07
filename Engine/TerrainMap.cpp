#include "TerrainMap.h"



TerrainMap::TerrainMap(const Surface* terrainFile)
	: width(terrainFile->GetWidth()), height(terrainFile->GetHeight())
{
	terrainMatrix = new bool[width * height];

	for (int x = 0; x < terrainFile->GetWidth(); x++)
		for (int y = 0; y < terrainFile->GetHeight(); y++)
			terrainMatrix[y * width + x] = (terrainFile->GetPixel(x, y) == Colors::Magenta) ? false : true;
}


TerrainMap::~TerrainMap()
{
	delete terrainMatrix;
}

bool TerrainMap::IsCollision(Vector<int> position)
{
	if (position.x < 0 || position.x >= width || position.y < 0 || position.y >= height)
		return false;

	return terrainMatrix[position.y * width + position.x];
}

int TerrainMap::GetMinYAtX(int x)
{
	if (x < 0 || x >= width)
		return 0;

	for (int y = 0; y < height; y++)
		if(terrainMatrix[y * width + x])
			return y;
}

int TerrainMap::GetWalkTarget(Vector<int> position)
{
	if (position.x < 0 || position.x >= width || position.y < 0 || position.y >= height)
		return position.y;

	if (IsCollision(position))
		for (int y = position.y; y >= 0; y--)
			if (!terrainMatrix[y * width + position.x])
				return y;

	for (int y = position.y; y <= height; y++)
		if (terrainMatrix[y * width + position.x])
			return y - 1;

	return position.y;
}
