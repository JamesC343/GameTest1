#ifndef PLAYER_H
#define PLAYER_H
#include "PhysicalObject.h"
#include "Entity.h"
#include "Surface.h"


class Player : public PhysicalObject, public Entity
{
    public:
        Player(Sprite*,Vei2,Vei2);
        virtual ~Player();
        void Routine(float);
        void Run(int);
        void Jump(int);

    protected:
    private:
};

#endif // PLAYER_H
