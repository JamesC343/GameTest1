#include "PhysicalObject.h"


PhysicalObject::PhysicalObject(Sprite* sprite, Vei2 position, Vei2 size, const bool isMovable)
		: sprite(sprite), hitBox (position, size.x - 1, size.y - 1), objectIsMovable(isMovable)
{
	assert(hitBox.GetWidth() % 2 == 0);
	assert(hitBox.GetHeight() % 2 == 0);

	velocityVector = { 0,0 };
	closeProximityZoneRadius = hitBox.GetMinRadius();
	//SetGrounded();
}

PhysicalObject::~PhysicalObject()
{
	delete sprite;
}

void PhysicalObject::Routine()
{
	CalculatePotentialZoneRadius();
}

void PhysicalObject::ApplyGravityAndFriction(float deltaTime)
{
	if (IsMovable())
	{
		int frictionFactor = 100 * (20) * deltaTime;

		if (isGrounded)
			frictionFactor = 750 * (20) * deltaTime;

		//Gravity
		if (!isGrounded)
			velocityVector.y += 2500 * (20) * deltaTime;

		//Friction
		if (velocityVector.x > frictionFactor)
			velocityVector.x -= frictionFactor;
		else if (velocityVector.x < -frictionFactor)
			velocityVector.x += frictionFactor;
		else
			velocityVector.x = 0;
	}
}

void PhysicalObject::Move(Vei2 move)
{
    hitBox.move(move);
	isGrounded = false;
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

int PhysicalObject::GetCloseProximityZoneRadius()
{
	return closeProximityZoneRadius;
}

int PhysicalObject::GetPotentialZoneRadius()
{
	return potentialZoneRadius;
}

bool PhysicalObject::IsMoving()
{
	//return !velocityVector.IsZero();
	if (velocityVector.GetLengthSq() > 0)
		return true;

	return false;
}

void PhysicalObject::CalculatePotentialZoneRadius()
{
	potentialZoneRadius = closeProximityZoneRadius + velocityVector.GetLength();
}

const bool PhysicalObject::IsMovable()
{
	return objectIsMovable;
}
