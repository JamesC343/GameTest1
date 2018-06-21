#include "Physics.h"

Physics::Physics(Player* target, std::vector<PhysicalObject*>* entities)
	: target (target), entities (entities)
{
    //ctor
}

Physics::~Physics()
{
    //dtor
}

void Physics::Routine(float deltaTime)
{
	PopulateMovingPhysicalObjects();
	//calculatePotentialZoneRadius
	GetProximatePairs();
	//getCollisionPairs();

	//moveObjectsToNewPosition
	
	
	
	MoveEntitiesLegacy(deltaTime);
}

void Physics::AddTerrainMap(int* newMap, Vei2 mapSize)
{
	terrainMap = newMap;
	worldSize = mapSize;
}

void Physics::PopulateMovingPhysicalObjects()
{
	movingPhysicalObjects.clear();

	PhysicalObject* loadObject;

	for (int i = 0; i < entities->size(); i++)
	{
		loadObject = entities->at(i);

		if (loadObject->IsMoving())
			movingPhysicalObjects.push_back(loadObject);
	}
}

void Physics::GetProximatePairs()
{
	PhysicalObject* objectA;
	PhysicalObject* objectB;

	while (!movingPhysicalObjects.empty() > 0)
	{
		objectA = movingPhysicalObjects.back();
		movingPhysicalObjects.pop_back();

		for (int i = 0; i < movingPhysicalObjects.size(); i++)
		{
			objectB = movingPhysicalObjects.at(i);

			if (objectA->IsPotentiallyProximate(objectB))
				proximatePairs.push_back({ objectA, objectB });
		}
	}
}

void Physics::MoveEntitiesLegacy(float deltaTime)
{
	for(int j = 0; j < entities->size(); j++)
	{
		PhysicalObject* entity = entities->at(j);
		RectI hitBox = entity->GetHitBox();

		Vector velocityVector = entity->GetVelocityVector();

		int xMove = velocityVector.x * deltaTime;
		int yMove = velocityVector.y * deltaTime;

		if(xMove < 0)
		    for (int i = 0; i > xMove; i--)
		        if (!IsCollisionLegacy(entity->GetHitBox(), Vei2(-1,0)))
					entity->Move({ -1, 0 });

		if(xMove > 0)
		    for (int i = 0; i < xMove; i++)
		        if (!IsCollisionLegacy(entity->GetHitBox(), Vei2(1,0)))
					entity->Move({ 1,0 });

		if(yMove < 0)
		    for (int i = 0; i > yMove; i--)
		        if (!IsCollisionLegacy(entity->GetHitBox(), Vei2(0,-1)))
					entity->Move({ 0,-1 });

		if(yMove > 0)
		    for (int i = 0; i < yMove; i++)
		        if (!IsCollisionLegacy(entity->GetHitBox(), Vei2(0,1)))
					entity->Move({ 0,1 });
		        else
		            entity->SetGrounded();
	}
}

bool Physics::IsCollisionLegacy(RectI hitBox, Vei2 move)
{
    int tileXMin, tileXMax, tileYMin, tileYMax;

	int xMin = hitBox.left / (20) + move.x;
    int xMax = hitBox.right / (20) + move.x;
	int yMin = hitBox.top / (20) + move.y;
    int yMax = hitBox.bottom / (20) + move.y;

    for (int i = 0; i < worldSize.x*worldSize.y; i++)
    {
        if (terrainMap[i] == 1)
        {
            tileXMin = i%worldSize.x * 40;
            tileXMax = (i%worldSize.x + 1) * 40 - 1;
            tileYMin = i/worldSize.x * 32;
            tileYMax = (i/worldSize.x + 1) * 32 - 1;

            if (xMax >= tileXMin && xMin <= tileXMax && yMax >= tileYMin && yMin <= tileYMax)
                return true;
        }
    }

    return false;
}
