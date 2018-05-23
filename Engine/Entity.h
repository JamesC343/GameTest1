#ifndef ENTITY_H
#define ENTITY_H

#include "Sprite.h"
#include "String.h"


class Entity
{
    public:									//Maybe one day these will belong to separate Interfaces
        Entity(std::string,RectI,Vei2,Vei2);//Entity that you can see, has a Sprite
        //Entity(Vei2,Vei2);				//Logical Entity, follows the same rules of physics
        virtual ~Entity();
		
        virtual void routine(float) = 0;
		
        Sprite getSprite();
        void move(Vei2);

		RectI getHitBox();
		int getXVelocity();
		int getYVelocity();
		void resetXVelocity();
		void resetYVelocity();

    protected:
        Sprite* sprite;
		RectI hitBox;//+SpriteBox

		int xVelocity, yVelocity, isGrounded;

    private:
		void entity();
};

#endif // ENTITY_H
