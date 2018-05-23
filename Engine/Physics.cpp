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
	moveEntities(deltaTime);
}

void Physics::addTerrainMap(int* newMap, Vei2 mapSize)
{
	terrainMap = newMap;
	worldSize = mapSize;
}

void Physics::moveEntities(float deltaTime)
{
	for(int j = 0; j < entities->size(); j++)
	{
		Entity* entity = entities->at(j);
		RectI hitBox = entity->getHitBox();

		int xVelocity = entity->getXVelocity();
		int yVelocity = entity->getYVelocity();

		int xMove = xVelocity * deltaTime;
		int yMove = yVelocity * deltaTime;

		if(xMove < 0)
		    for (int i = 0; i > xMove; i--)
		        if (!isCollision(entity->getHitBox(), Vei2(-1,0)))
					entity->move({ -1, 0 });
//		        else
//		            player->resetXForce();

		if(xMove > 0)
		    for (int i = 0; i < xMove; i++)
		        if (!isCollision(entity->getHitBox(), Vei2(1,0)))
					entity->move({ 1,0 });
//		          else
//		              player->resetXForce();

		if(yMove < 0)
		    for (int i = 0; i > yMove; i--)
		        if (!isCollision(entity->getHitBox(), Vei2(0,-1)))
					entity->move({ 0,-1 });
//		        else
//		            entity->resetYVelocity();

		if(yMove > 0)
		    for (int i = 0; i < yMove; i++)
		        if (!isCollision(entity->getHitBox(), Vei2(0,1)))
					entity->move({ 0,1 });
		        else
		            entity->resetYVelocity();
	}
}

bool Physics::isCollision(RectI hitBox, Vei2 move)
{
    int tileXMin, tileXMax, tileYMin, tileYMax;

	int xMin = hitBox.left + move.x;
    int xMax = hitBox.right + move.x;
	int yMin = hitBox.top + move.y;
    int yMax = hitBox.bottom + move.y;

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
