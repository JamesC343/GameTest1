#include "TerrainObject.h"



TerrainObject::TerrainObject(Sprite* sprite, Vei2 position, Vei2 size)
	: PhysicalObject(sprite, position, size, false)
{
}


TerrainObject::~TerrainObject()
{
}
