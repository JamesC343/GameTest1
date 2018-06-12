#include "PhysicalObject.h"


PhysicalObject::PhysicalObject(std::string spritePath, RectI rect, Vei2 size, Vei2 position)
		: hitBox (position, size.x - 1, size.y - 1)
{
	sprite = new Sprite(spritePath, rect);

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
	velocityVector.y += 1000 * (20) * deltaTime;

	//Friction
	if (velocityVector.x > frictionFactor)
		velocityVector.x -= frictionFactor;
	else if (velocityVector.x < -frictionFactor)
		velocityVector.x += frictionFactor;
	else
		velocityVector.x = 0;
}

Sprite PhysicalObject::getSprite()
{
	return *sprite;
}

void PhysicalObject::move(Vei2 move)
{
    hitBox.move(move);
}

RectI PhysicalObject::getHitBox()
{
	return hitBox;
}

Vector PhysicalObject::getVelocityVector()
{
	return velocityVector;
}

void PhysicalObject::setGrounded()
{
	velocityVector.y = 0;
	isGrounded = true;
}
