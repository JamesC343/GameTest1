#include "TerrainObject.h"



TerrainObject::TerrainObject(Sprite* sprite, Vei2 size, Vei2 position)
	: PhysicalObject(sprite, size, position, false)
{
}


TerrainObject::~TerrainObject()
{
}
