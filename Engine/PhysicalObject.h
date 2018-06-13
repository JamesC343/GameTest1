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

		void applyGravityAndFriction(float);
        void move(Vei2);
		void setGrounded();

		Sprite getSprite();
		RectI getHitBox();
		RectI getSpriteBox();
		Vector getVelocityVector();

    protected:
		const bool isMovable();
		Vector velocityVector;
		bool isGrounded;

    private:
		const bool objectIsMovable;
		Sprite * sprite;
		RectI hitBox;
		RectI spriteBox;
};

#endif // ENTITY_H
