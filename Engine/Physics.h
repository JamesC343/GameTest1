#ifndef PHYSICS_H
#define PHYSICS_H

#include <vector>
#include <iostream>
#include "Player.h"
#include "TerrainObject.h"
#include "Vector.h"

/*struct PhysicalObjectPair
{
	PhysicalObject* a;
	PhysicalObject* b;
};*/

struct terrainCollision
{
	float collisionTime = -1;
	int collisionType = -1;//0,1,2,3, 4 - left,right,up,down, notGrounded
	Vector<int> distance = { 0,0 };
};

class Physics
{
    public:
        Physics(Player*, std::vector<TerrainObject*>*, std::vector<Entity*>*);
        virtual ~Physics();
		void Routine(float);
		void Debug();

    protected:

    private:
		std::vector<Entity*> GetMovingEntities();
		std::vector<TerrainObject*> GetProximateTerrain(Entity*, float);
		terrainCollision GetNextTerrainCollision(Entity*, std::vector<TerrainObject*>, float);

		bool IsCollision(Vector<int>, RectI);
		//std::vector<PhysicalObjectPair> GetProximatePairs(std::vector<PhysicalObject*>, float);
		//std::vector<Collision> GetCollisionPairs(std::vector<PhysicalObjectPair>);

		Player* target;
		std::vector<TerrainObject*>* terrainObjects;
		std::vector<Entity*>* entities;

		bool debugOnThisFrame = false;
};

#endif // PHYSICS_H
