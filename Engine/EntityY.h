#ifndef ENTITYY_H
#define ENTITYY_H
#include "PhysicalObject.h"
#include "Entity.h"
#include "Surface.h"


class EntityY : public Entity //public PhysicalObject, public Entity
{
    public:
        EntityY(Sprite*,Vector<int>, Vector<int>, std::string);
        ~EntityY();
        void Routine(float) override;

    protected:
    private:
        void DecisionMaking();
        void Run(int);
        void Jump(int);
};

#endif // ENTITYY_H
