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
		void GetMovingPhysicalObjects();
		void GetProximatePairs();
		void GetCollisionPairs();
		void MoveEntitiesLegacy(float);
		bool IsCollisionLegacy(RectI,Vei2);

		struct PhysicalObjectPair
		{
			PhysicalObject* a;
			PhysicalObject* b;
		};

		struct Collision
		{
			PhysicalObjectPair objectPair;
			const float collisionTime;
		};

		Player* target;
		std::vector<PhysicalObject*>* physicalObjects;
		std::vector<PhysicalObject*>* entities; //Legacy
		std::vector<PhysicalObject*> movingPhysicalObjects;
		std::vector<PhysicalObjectPair> proximatePairs;
		std::vector<Collision> collisions;

		int* terrainMap;
		Vei2 worldSize;
};

#endif // PHYSICS_H
