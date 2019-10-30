#ifndef ENTITY_H
#define ENTITY_H

#include "Sprite.h"
#include "String.h"
#include "Vector.h"
#include <assert.h>


class PhysicalObject
{
    public:
		PhysicalObject(Sprite*, Vector<int>, Vector<int>, std::string);
        virtual ~PhysicalObject() = 0;

		virtual void Routine();
		const std::string GetName();

		virtual void Move(Vector<int>);

		Sprite GetSprite();
		RectI GetHitBox();
		RectI GetSpriteBox();
		int GetCloseProximityZoneRadius();

    protected:

    private:
		int closeProximityZoneRadius = 0;

		Sprite * sprite;
		RectI hitBox = { 0,0,0,0 };
		RectI spriteBox = { 0,0,0,0 };

		std::string name;
};

#endif // ENTITY_H
