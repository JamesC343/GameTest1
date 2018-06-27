#include "Physics.h"

Physics::Physics(Player* target, std::vector<PhysicalObject*>* physicalObjects)
	: target (target), physicalObjects(physicalObjects), entities(physicalObjects)
{
    //ctor
}

Physics::~Physics()
{
    //dtor
}

void Physics::Routine(float deltaTime)
{
	GetMovingPhysicalObjects();
	GetProximatePairs();
	GetCollisionPairs();

	float collisionTime = 0;

	for (int i = 0; i < collisions.size(); i++)
		if (i == 0 || collisions.at(i).collisionTime < collisionTime)
			collisionTime = collisions.at(i).collisionTime;

	//moveObjects(deltaTime)
	
	if (proximatePairs.size() > 0)
		int i = 0;
	
	MoveEntitiesLegacy(deltaTime);
}

void Physics::AddTerrainMap(int* newMap, Vei2 mapSize)
{
	terrainMap = newMap;
	worldSize = mapSize;
}

void Physics::GetMovingPhysicalObjects()
{
	movingPhysicalObjects.clear();

	PhysicalObject* objectA;

	for (int i = 0; i < physicalObjects->size(); i++)
	{
		objectA = physicalObjects->at(i);

		if (objectA->IsMoving())
			movingPhysicalObjects.push_back(objectA);
	}
}

void Physics::GetProximatePairs()
{
	proximatePairs.clear();

	PhysicalObject* objectA;
	PhysicalObject* objectB;

	for (int i = 0; i < movingPhysicalObjects.size(); i++)
	{
		objectA = movingPhysicalObjects.at(i);

		for (int j = 0; j < physicalObjects->size(); j++)
		{
			objectB = physicalObjects->at(j);

			if (objectA != objectB)
			{
				int distance = (objectA->GetHitBox().GetCenter() - objectB->GetHitBox().GetCenter()).GetLength();
				int objectAZoneRadius = objectA->GetPotentialZoneRadius();
				int objectBZoneRadius = objectB->GetPotentialZoneRadius();

				if(distance <= objectAZoneRadius + objectBZoneRadius)
					proximatePairs.push_back({ objectA, objectB });
			}
		}
	}
}

void Physics::GetCollisionPairs()
{
	collisions.clear();

	PhysicalObjectPair proximatePair;

	if (proximatePairs.size() > 1)
		int breakpoint = 0;

	for (int i = 0; i < proximatePairs.size(); i++)
	{
		proximatePair = proximatePairs.at(i);

		int xDistance = proximatePair.a->GetHitBox().GetCenter().x - proximatePair.b->GetHitBox().GetCenter().x;
		int yDistance = proximatePair.a->GetHitBox().GetCenter().y - proximatePair.b->GetHitBox().GetCenter().y;

		int xVelocity = proximatePair.a->GetVelocityVector().x - proximatePair.b->GetVelocityVector().x;
		int yVelocity = proximatePair.a->GetVelocityVector().y - proximatePair.b->GetVelocityVector().y;

		int proximityZoneA = proximatePair.a->GetCloseProximityZoneRadius();
		int proximityZoneB = proximatePair.b->GetCloseProximityZoneRadius();

		int a = (xVelocity * xVelocity + yVelocity * yVelocity);
		int b = (2 * xVelocity * xDistance + 2 * yVelocity * yDistance);
		int c = (xDistance * xDistance + yDistance * yDistance + (proximityZoneA + proximityZoneB) * (proximityZoneA + proximityZoneB));

		if (b * b >= 4 * a * c)
		{
			const float deltaTime = 0;
			collisions.push_back({ proximatePair, deltaTime });
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
