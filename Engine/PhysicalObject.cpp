#include "PhysicalObject.h"


PhysicalObject::PhysicalObject(Sprite* sprite, Vei2 size, Vei2 position, const bool isMovable)
		: sprite(sprite), hitBox (position, size.x - 1, size.y - 1), objectIsMovable(isMovable)
{
	velocityVector = { 0,0 };
	closeProximityZoneRadius = hitBox.GetMinRadius();
	SetGrounded();
}

PhysicalObject::~PhysicalObject()
{
	delete sprite;
}

void PhysicalObject::ApplyGravityAndFriction(float deltaTime)
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

void PhysicalObject::Move(Vei2 move)
{
    hitBox.move(move);
}

void PhysicalObject::SetGrounded()
{
	velocityVector.y = 0;
	isGrounded = true;
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

Vector PhysicalObject::GetVelocityVector()
{
	return velocityVector;
}

bool PhysicalObject::IsMoving()
{
	return !velocityVector.IsZero();
}

bool PhysicalObject::IsPotentiallyProximate(PhysicalObject * other)
{
	int distance = (hitBox.GetCenter() - other->GetHitBox().GetCenter()).GetLength();

	if (distance < potentialZoneRadius + other->potentialZoneRadius)
		return true;

	return false;
}

const bool PhysicalObject::IsMovable()
{
	return objectIsMovable;
}
