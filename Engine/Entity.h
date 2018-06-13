#pragma once
class Entity
{
public:
	Entity();
	virtual ~Entity();

	virtual void routine(float) = 0;
};

