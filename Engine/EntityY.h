#ifndef ENTITYY_H
#define ENTITYY_H
#include "PhysicalObject.h"
#include "Surface.h"


class EntityY : public PhysicalObject
{
    public:
        EntityY(std::string,RectI,Vei2, Vei2);
        virtual ~EntityY();
        void routine(float);

    protected:
    private:
        void decisionMaking();
        void run(int);
        void jump(int);
};

#endif // ENTITYY_H
