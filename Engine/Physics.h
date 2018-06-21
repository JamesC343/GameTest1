#ifndef PHYSICS_H
#define PHYSICS_H

#include <vector>
#include "Player.h"

class Physics
{
    public:
        Physics(Player*,std::vector<PhysicalObject*>*);
        virtual ~Physics();
		void Routine(float);
		void AddTerrainMap(int*,Vei2);

    protected:

    private:
		void PopulateMovingPhysicalObjects();
		void GetProximatePairs();
		void MoveEntitiesLegacy(float);
		bool IsCollisionLegacy(RectI,Vei2);

		struct physicalObjectPair
		{
			PhysicalObject* a;
			PhysicalObject* b;
		};

		Player* target;
		std::vector<PhysicalObject*>* entities;
		std::vector<PhysicalObject*> movingPhysicalObjects;
		std::vector<physicalObjectPair> proximatePairs;

		int* terrainMap;
		Vei2 worldSize;
};

#endif // PHYSICS_H
