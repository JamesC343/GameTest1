#include "Entity.h"


Entity::Entity(std::string spritePath, RectI rect, Vei2 size, Vei2 position)
		: hitBox (position, size.x - 1, size.y - 1)
{
	sprite = new Sprite(spritePath, rect);

	xVelocity = 0;
	yVelocity = 0;
	isGrounded = false;
}

Entity::~Entity()
{
	delete sprite;
}

Sprite Entity::getSprite()
{
	return *sprite;
}

void Entity::move(Vei2 move)
{
    hitBox.move(move);
}

RectI Entity::getHitBox()
{
	return hitBox;
}

int Entity::getXVelocity()
{
	return xVelocity;
}

int Entity::getYVelocity()
{
	return yVelocity;
}

void Entity::resetXVelocity()
{
	xVelocity = 0;
}

void Entity::resetYVelocity()
{
	yVelocity = 0;
	isGrounded = true;
}

void Entity::entity()
{
    xVelocity = 0;
	yVelocity = 0;
}
