#include "TerrainObject.h"



TerrainObject::TerrainObject(Sprite* sprite, Vector<int> position, Vector<int> size, std::string name)
	: PhysicalObject(sprite, position, size, name)
{
}


TerrainObject::~TerrainObject()
{
}
