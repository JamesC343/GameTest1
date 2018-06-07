#include "Physics.h"

Physics::Physics(Player* target, std::vector<Entity*>* entities)
	: target (target), entities (entities)
{
    //ctor
}

Physics::~Physics()
{
    //dtor
}

void Physics::routine(float deltaTime)
{
	moveEntitiesLegacy(deltaTime);
}

void Physics::addTerrainMap(int* newMap, Vei2 mapSize)
{
	terrainMap = newMap;
	worldSize = mapSize;
}

void Physics::moveEntitiesLegacy(float deltaTime)
{
	for(int j = 0; j < entities->size(); j++)
	{
		Entity* entity = entities->at(j);
		RectI hitBox = entity->getHitBox();

		Vector velocityVector = entity->getVelocityVector();

		int xMove = velocityVector.x * deltaTime;
		int yMove = velocityVector.y * deltaTime;

		if(xMove < 0)
		    for (int i = 0; i > xMove; i--)
		        if (!isCollisionLegacy(entity->getHitBox(), Vei2(-1,0)))
					entity->move({ -1, 0 });

		if(xMove > 0)
		    for (int i = 0; i < xMove; i++)
		        if (!isCollisionLegacy(entity->getHitBox(), Vei2(1,0)))
					entity->move({ 1,0 });

		if(yMove < 0)
		    for (int i = 0; i > yMove; i--)
		        if (!isCollisionLegacy(entity->getHitBox(), Vei2(0,-1)))
					entity->move({ 0,-1 });

		if(yMove > 0)
		    for (int i = 0; i < yMove; i++)
		        if (!isCollisionLegacy(entity->getHitBox(), Vei2(0,1)))
					entity->move({ 0,1 });
		        else
		            entity->setGrounded();
	}
}

bool Physics::isCollisionLegacy(RectI hitBox, Vei2 move)
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
