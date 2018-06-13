#include "PhysicalObject.h"


PhysicalObject::PhysicalObject(Sprite* sprite, Vei2 size, Vei2 position, const bool isMovable)
		: sprite(sprite), hitBox (position, size.x - 1, size.y - 1), objectIsMovable(isMovable)
{
	velocityVector = { 0,0 };
	setGrounded();
}

PhysicalObject::~PhysicalObject()
{
	delete sprite;
}

void PhysicalObject::applyGravityAndFriction(float deltaTime)
{
	int frictionFactor = 100 * (20) * deltaTime;

	if (isGrounded)
		frictionFactor = 750 * (20) * deltaTime;

	//Gravity
	velocityVector.y += 2500 * (20) * deltaTime;

	//Friction
	if (velocityVector.x > frictionFactor)
		velocityVector.x -= frictionFactor;
	else if (velocityVector.x < -frictionFactor)
		velocityVector.x += frictionFactor;
	else
		velocityVector.x = 0;
}

void PhysicalObject::move(Vei2 move)
{
    hitBox.move(move);
}

void PhysicalObject::setGrounded()
{
	velocityVector.y = 0;
	isGrounded = true;
}

Sprite PhysicalObject::getSprite()
{
	return *sprite;
}

RectI PhysicalObject::getHitBox()
{
	return hitBox;
}

RectI PhysicalObject::getSpriteBox()
{
	return spriteBox;
}

Vector PhysicalObject::getVelocityVector()
{
	return velocityVector;
}

const bool PhysicalObject::isMovable()
{
	return objectIsMovable;
}
