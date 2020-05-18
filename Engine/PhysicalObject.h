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
		PhysicalObject(Sprite*, Vector<int>);
        virtual ~PhysicalObject() = 0;

		virtual void Routine();
		const std::string GetName();

		virtual void Move(Vector<int>);

		Sprite* GetSprite();
		RectI GetHitBox();
		Vector<int> GetTopLeft();
		int GetMinY(int);
		int GetMaxY(int);

    protected:

    private:
		void BuildCollisionMap();
		bool ValidPosition(Vector<int>);

		Sprite * sprite;
		Vector<int> size;
		Vector<int> position;
		int* minY;
		int* maxY;

		std::string name;
};

#endif // ENTITY_H
