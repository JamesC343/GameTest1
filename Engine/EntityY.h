#ifndef ENTITYY_H
#define ENTITYY_H
#include "Entity.h"
#include "Surface.h"


class EntityY : public Entity
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
