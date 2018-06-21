#pragma once
class Entity
{
public:
	Entity();
	virtual ~Entity();

	virtual void Routine(float) = 0;
};

