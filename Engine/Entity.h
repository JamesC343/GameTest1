#pragma once
#include "PhysicalObject.h"
class Entity : public PhysicalObject
{
public:
	Entity(Sprite*, Vector<int>, Vector<int>, std::string);
	virtual ~Entity() = 0;

	virtual void Routine(float) = 0;
	void Move(float);
	void Move(Vector<int>);
	void SetXCollision();
	void SetYCollision();
	void SetGrounded(bool);

	Vector<int> GetVelocityVector();
	bool GetIsGrounded();
	bool IsMoving();

protected:
	void ApplyGravityAndFriction(float);
	void addVelocity(Vector<int>);

	bool isGrounded = false;
private:
	Vector<int> velocityVector = { 0,0 };
};

