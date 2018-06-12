#ifndef PHYSICS_H
#define PHYSICS_H

#include <vector>
#include "Player.h"

class Physics
{
    public:
        Physics(Player*,std::vector<PhysicalObject*>*);
        virtual ~Physics();
		void routine(float);
		void addTerrainMap(int*,Vei2);

    protected:

    private:
		void moveEntitiesLegacy(float);
		bool isCollisionLegacy(RectI,Vei2);

		Player* target;
		std::vector<PhysicalObject*>* entities;

		int* terrainMap;
		Vei2 worldSize;
};

#endif // PHYSICS_H
