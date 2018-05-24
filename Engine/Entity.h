#ifndef ENTITY_H
#define ENTITY_H

#include "Sprite.h"
#include "String.h"
#include "Vector.h"


class Entity
{
    public:
        Entity(std::string,RectI,Vei2,Vei2);
        virtual ~Entity();
		
        virtual void routine(float) = 0;

		void applyGravityAndFriction(float);
		Sprite getSprite();
        void move(Vei2);

		RectI getHitBox();
		Vector getVelocityVector();
		void setGrounded();

    protected:
        Sprite* sprite;
		RectI hitBox;//+SpriteBox
		Vector velocityVector;
		bool isGrounded;

    private:
};

#endif // ENTITY_H
