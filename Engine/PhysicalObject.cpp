#include "PhysicalObject.h"
#include <iostream>


PhysicalObject::PhysicalObject(Sprite* sprite, Vector<int> position, Vector<int> size, std::string name)
		: sprite(sprite), name(name), size(size), position(position)
{
	BuildCollisionMap();
}

PhysicalObject::PhysicalObject(Sprite* sprite, Vector<int> position)
		: sprite(sprite), position(position), size({ sprite->getSurface().GetWidth(), sprite->getSurface().GetHeight() })
{
	BuildCollisionMap();
}

void PhysicalObject::BuildCollisionMap()
{
	minY = new int[size.x];
	maxY = new int[size.x];

	Surface& surface = sprite->getSurface();
	for (int x = 0; x < surface.GetWidth(); x++)
	{
		//Finding minY
		minY[x] = -1;
		for (int y = 0; y < surface.GetHeight() && minY[x] == -1; y++)
			if (surface.GetPixel(x, y) != Colors::Magenta)
				minY[x] = y;

		//Finding maxY
		maxY[x] = -1;
		for (int y = surface.GetHeight() - 1; y >= 0 && maxY[x] == -1; y--)
			if (surface.GetPixel(x, y) != Colors::Magenta)
				maxY[x] = y;
	}
}

PhysicalObject::~PhysicalObject()
{
	delete sprite;
}

void PhysicalObject::Routine()
{
}

const std::string PhysicalObject::GetName()
{
	return name;
}

void PhysicalObject::Move(Vector<int> move)
{
	position += move;
}

Sprite* PhysicalObject::GetSprite()
{
	return sprite;
}

RectI PhysicalObject::GetHitBox()
{
	return RectI(position, size.x, size.y);
}

Vector<int> PhysicalObject::GetTopLeft()
{
	return position;
}

int PhysicalObject::GetMinY(int x)
{
	if (ValidPosition({ x, 0 }))
		return minY[x];

	return 0;
}

int PhysicalObject::GetMaxY(int x)
{
	if (ValidPosition({ x, 0 }))
		return maxY[x];

	return 0;
}

bool PhysicalObject::ValidPosition(Vector<int> position)
{
	if (position.x < 0 || position.x >= size.x || position.y < 0 || position.y >= size.y)
		return false;

	return true;
}
