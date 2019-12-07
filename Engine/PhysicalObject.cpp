#include "PhysicalObject.h"
#include <iostream>


PhysicalObject::PhysicalObject(Sprite* sprite, Vector<int> position, Vector<int> size, std::string name)
		: sprite(sprite), hitBox (position, size.x - 1, size.y - 1), name(name)
{
	closeProximityZoneRadius = hitBox.GetMinRadius();
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
	hitBox.Move(move);
}

Sprite PhysicalObject::GetSprite()
{
	return *sprite;
}

RectI PhysicalObject::GetHitBox()
{
	return hitBox;
}

RectI PhysicalObject::GetSpriteBox()
{
	return spriteBox;
}

int PhysicalObject::GetCloseProximityZoneRadius()
{
	return closeProximityZoneRadius;
}