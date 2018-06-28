#ifndef ENTITY_H
#define ENTITY_H

#include "Sprite.h"
#include "String.h"
#include "Vector.h"
#include <assert.h>


class PhysicalObject
{
    public:
		PhysicalObject(Sprite*,Vei2,Vei2,const bool);
        virtual ~PhysicalObject() = 0;

		void Routine();

		void ApplyGravityAndFriction(float);
        void Move(Vei2);
		void SetGrounded();
		void CalculatePotentialZoneRadius();

		Sprite GetSprite();
		RectI GetHitBox();
		RectI GetSpriteBox();
		Vector GetVelocityVector();
		int GetCloseProximityZoneRadius();
		int GetPotentialZoneRadius();
		bool IsMoving();

    protected:
		const bool IsMovable();
		Vector velocityVector = { 0,0 };
		bool isGrounded = false;

    private:
		const bool objectIsMovable = false;
		int closeProximityZoneRadius = 0;
		int potentialZoneRadius = 0;

		Sprite * sprite;
		RectI hitBox = { 0,0,0,0 };
		RectI spriteBox = { 0,0,0,0 };
};

#endif // ENTITY_H
