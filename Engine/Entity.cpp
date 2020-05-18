#include "Entity.h"



Entity::Entity(Sprite* sprite, Vector<int> position, Vector<int> size, std::string name)
	: PhysicalObject(sprite, position, size, name)
{
	forceVector = { 0,0 };
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
	isGrounded = newValue;
}

Vector<int> Entity::GetForceVector()
{
	return forceVector;
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
	return forceVector.x != 0 || forceVector.y != 0 || velocityVector.x != 0 || velocityVector.y != 0;
}

RectI Entity::GetHitBox()
{
	return PhysicalObject::GetHitBox();
}

RectI Entity::GetHitBox(float deltaTime)
{
	RectI newPosition = PhysicalObject::GetHitBox();
	int xMove = (velocityVector.x * deltaTime);
	int yMove = (velocityVector.y * deltaTime);
	
	newPosition.Move({ xMove, yMove });

	return newPosition;
}

RectI Entity::GetHitBox(Vector<int> move)
{
	RectI newPosition = PhysicalObject::GetHitBox();
	newPosition.Move(move);

	return newPosition;
}

int Entity::GetWeight()
{
	return weight;
}

void Entity::ApplyGravityAndFriction(float deltaTime)
{
	//Temp workaround
	velocityVector = forceVector;
	//

	int frictionFactor = 100 * deltaTime;

	if (isGrounded)
		frictionFactor = 750 * deltaTime;

	//Gravity
	if (isGrounded)
		forceVector.y = (int)(5000.0 * deltaTime);	//This keeps the player grounded when running down slopes but can still fall if the slope is too steep
														//Realistically this value is too high but if set to a normal value then the fall collision causes jittering
														//The solution will be to implement fall collisions that set the y value relative to slope instead of just setting y = 0
	else
		forceVector.y += (int)(2500.0 * deltaTime);

	//Friction
	if (forceVector.x > frictionFactor)
		forceVector.x -= frictionFactor;
	else if (forceVector.x < -frictionFactor)
		forceVector.x += frictionFactor;
	else
		forceVector.x = 0;
}

void Entity::AddForce(Vector<int> force)
{
	forceVector += force;
}

void Entity::AddVelocity(Vector<int> velocity)
{
	velocityVector += velocity;
}
