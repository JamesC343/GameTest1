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

	Vector<int> GetForceVector();
	Vector<int> GetVelocityVector();
	bool GetIsGrounded();
	bool IsMoving();
	RectI GetHitBox();
	RectI GetHitBox(float);
	RectI GetHitBox(Vector<int>);
	int GetWeight();

protected:
	void ApplyGravityAndFriction(float);
	void AddForce(Vector<int>);
	void AddVelocity(Vector<int>);

	bool isGrounded = false;
private:
	Vector<int> forceVector = { 0,0 };
	Vector<int> velocityVector = { 0,0 };
	int weight = 1;
};

