#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
#include "Surface.h"


class Player : public Entity
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
