#include "Entity.h"



Entity::Entity(Sprite* sprite, Vector<int> position, Vector<int> size, std::string name)
	: PhysicalObject(sprite, position, size, name)
{
	velocityVector = { 0,0 };
}


Entity::~Entity()
{
}

void Entity::Move(float deltaTime)
{
	int xMove = (velocityVector.x * deltaTime);
	int yMove = (velocityVector.y * deltaTime);

	PhysicalObject::Move({ xMove, yMove });
}

void Entity::Move(Vector<int> move)
{
	PhysicalObject::Move(move);
}

void Entity::SetXCollision()
{
	velocityVector.x = 0;
}

void Entity::SetYCollision()
{
	velocityVector.y = 0;
}

void Entity::SetGrounded(bool newValue)
{
	velocityVector.y = 0;
	isGrounded = newValue;
}

Vector<int> Entity::GetVelocityVector()
{
	return velocityVector;
}

bool Entity::GetIsGrounded()
{
	return isGrounded;
}

bool Entity::IsMoving()
{
	return velocityVector.x != 0 || velocityVector.y != 0;
}

void Entity::ApplyGravityAndFriction(float deltaTime)
{
	int frictionFactor = 100 * (20) * deltaTime;

	if (isGrounded)
		frictionFactor = 750 * (20) * deltaTime;

	//Gravity
	if (!isGrounded)
		velocityVector.y += (int)(2500.0 * (20.0) * deltaTime);

	//Friction
	if (velocityVector.x > frictionFactor)
		velocityVector.x -= frictionFactor;
	else if (velocityVector.x < -frictionFactor)
		velocityVector.x += frictionFactor;
	else
		velocityVector.x = 0;
}

void Entity::addVelocity(Vector<int> velocity)//Vector velocity)
{
	velocityVector += velocity;
}
