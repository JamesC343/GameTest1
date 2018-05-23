#ifndef PHYSICS_H
#define PHYSICS_H

#include <vector>
#include "Player.h"

class Physics
{
    public:
        Physics(Player*,std::vector<Entity*>*);
        virtual ~Physics();
		void routine(float);
		void addTerrainMap(int*,Vei2);

    protected:

    private:
		void moveEntities(float);
		bool isCollision(RectI,Vei2);

		Player* target;
		std::vector<Entity*>* entities;

		int* terrainMap;
		Vei2 worldSize;
};

#endif // PHYSICS_H
