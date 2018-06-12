#ifndef PLAYER_H
#define PLAYER_H
#include "PhysicalObject.h"
#include "Surface.h"


class Player : public PhysicalObject
{
    public:
        Player(std::string,RectI,Vei2,Vei2);
        virtual ~Player();
        void routine(float);
        void run(int);
        void jump(int);

    protected:
    private:
};

#endif // PLAYER_H
