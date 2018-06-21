#ifndef ENTITYY_H
#define ENTITYY_H
#include "PhysicalObject.h"
#include "Entity.h"
#include "Surface.h"


class EntityY : public PhysicalObject, public Entity
{
    public:
        EntityY(Sprite*,Vei2, Vei2);
        virtual ~EntityY();
        void Routine(float);

    protected:
    private:
        void DecisionMaking();
        void Run(int);
        void Jump(int);
};

#endif // ENTITYY_H
