#ifndef ENTITY_H
#define ENTITY_H

#include "Sprite.h"
#include "String.h"
#include "Vector.h"


class PhysicalObject
{
    public:
		PhysicalObject(Sprite*,Vei2,Vei2,const bool);
        virtual ~PhysicalObject() = 0;

		void ApplyGravityAndFriction(float);
        void Move(Vei2);
		void SetGrounded();

		Sprite GetSprite();
		RectI GetHitBox();
		RectI GetSpriteBox();
		Vector GetVelocityVector();
		bool IsMoving();
		bool IsPotentiallyProximate(PhysicalObject *other);

    protected:
		const bool IsMovable();
		Vector velocityVector;
		bool isGrounded;

    private:
		const bool objectIsMovable;
		int closeProximityZoneRadius;
		int potentialZoneRadius;
		Sprite * sprite;
		RectI hitBox;
		RectI spriteBox;
};

#endif // ENTITY_H
