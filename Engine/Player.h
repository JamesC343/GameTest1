#ifndef PLAYER_H
#define PLAYER_H
#include "PhysicalObject.h"
#include "Entity.h"
#include "Surface.h"


class Player : public Entity
{
    public:
		Player(Sprite*, Vector<int>, Vector<int>, std::string);
        ~Player();
		void Routine(float) override;
        void Run(int);
        void Jump(int);

		void AddForce(Vector<int>);
		void AddVelocity(Vector<int>);

    protected:
    private:
};

#endif // PLAYER_H
