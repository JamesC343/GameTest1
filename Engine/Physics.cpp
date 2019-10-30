#include "Physics.h"

Physics::Physics(Player* target, std::vector<TerrainObject*>* terrainObjects, std::vector<Entity*>* entities)
	: target (target), terrainObjects(terrainObjects), entities(entities)
{
    //ctor
}

Physics::~Physics()
{
    //dtor
}

void Physics::Routine(float deltaTime)//Isn't it funny how an x collision causes y distance to be reduced? This applies to both jumping up and also falling back down
{
	std::vector<Entity*> movingEntities = GetMovingEntities();
	
	for (int i = 0; i < movingEntities.size(); i++)
	{
		Entity* entity = movingEntities.at(i);
		float elapsedDeltaTime = 0;

		while (elapsedDeltaTime < deltaTime)
		{
			std::vector<TerrainObject*> proximateTerrain = GetProximateTerrain(entity, deltaTime - elapsedDeltaTime);
			terrainCollision nextCollision = GetNextTerrainCollision(entity, proximateTerrain, deltaTime - elapsedDeltaTime);
			if (nextCollision.collisionTime != -1)
			{
				assert(nextCollision.collisionTime != 0);
				elapsedDeltaTime += nextCollision.collisionTime;

				entity->Move(nextCollision.distance);
				
				switch (nextCollision.collisionType)
				{//0,1,2,3 - left,right,up,down
				case 0:
					entity->SetXCollision();
					break;
				case 1:
					entity->SetXCollision();
					break;
				case 2:
					entity->SetYCollision();
					break;
				case 3:
					//std::cout << "SetGrounded True\n";
					entity->SetGrounded(true);
					break;
				case 4:
					//std::cout << "SetGrounded False\n";
					entity->SetGrounded(false);
					break;
				}
			}
			else
				entity->Move(deltaTime - elapsedDeltaTime), elapsedDeltaTime = deltaTime;
		}
	}
}

void Physics::Debug()
{
	debugOnThisFrame = true;
}

std::vector<Entity*> Physics::GetMovingEntities()
{
	std::vector<Entity*> movingEntities;

	for (int i = 0; i < entities->size(); i++)
		if (entities->at(i)->IsMoving())
			movingEntities.push_back(entities->at(i));

	return movingEntities;
}

std::vector<TerrainObject*> Physics::GetProximateTerrain(Entity* entity, float deltaTime)
{
	std::vector<TerrainObject*> proximateTerrain;
	TerrainObject* terrain;

	int entityVelocityLength = entity->GetVelocityVector().GetLength() * deltaTime;

	for (int j = 0; j < terrainObjects->size(); j++)
	{
		terrain = terrainObjects->at(j);

		int distance = (entity->GetHitBox().GetCenter() - terrain->GetHitBox().GetCenter()).GetLength();

		if (distance <= entity->GetCloseProximityZoneRadius() + terrain->GetCloseProximityZoneRadius() + entityVelocityLength)
			proximateTerrain.push_back(terrain);
	}

	return proximateTerrain;
}

terrainCollision Physics::GetNextTerrainCollision(Entity* entity, std::vector<TerrainObject*> proximateTerrain, float deltaTime)
{
	terrainCollision collision;
	std::vector<terrainCollision> collisions;

	RectI entityHitBox = entity->GetHitBox();
	Vector<float> velocityVector = entity->GetVelocityVector();

	PhysicalObject* terrain;
	RectI terrainHitBox;

	float xCollisionTime = -1;
	float yCollisionTime = -1;
	Vector<int> collisionDistance = { 0,0 };
	int collisionType = -1;
	
	//Check for collisions
	for (int i = 0; i < proximateTerrain.size(); i++)
	{
		terrain = proximateTerrain.at(i);
		terrainHitBox = terrain->GetHitBox();

		assert(!(entityHitBox.right >= terrainHitBox.left && entityHitBox.left <= terrainHitBox.right && entityHitBox.bottom >= terrainHitBox.top && entityHitBox.top <= terrainHitBox.bottom));

		xCollisionTime = ((entityHitBox.right < terrainHitBox.left || entityHitBox.left > terrainHitBox.right) && velocityVector.x == 0) ? -1
			: (entityHitBox.right < terrainHitBox.left) ? (terrainHitBox.left - entityHitBox.right) / velocityVector.x
			: (entityHitBox.left > terrainHitBox.right) ? (terrainHitBox.right - entityHitBox.left) / velocityVector.x : 0;

		yCollisionTime = ((entityHitBox.bottom < terrainHitBox.top || entityHitBox.top > terrainHitBox.bottom) && velocityVector.y == 0) ? -1
			: (entityHitBox.bottom < terrainHitBox.top) ? (terrainHitBox.top - entityHitBox.bottom) / velocityVector.y
			: (entityHitBox.top > terrainHitBox.bottom) ? (terrainHitBox.bottom - entityHitBox.top) / velocityVector.y : 0;

		//--Now that Physics moves objects by distance specifically instead of time, could consider to re-simplify this function
		collisionDistance.x = (entityHitBox.right < terrainHitBox.left) ? terrainHitBox.left - entityHitBox.right - 1
			: (entityHitBox.left > terrainHitBox.right) ? terrainHitBox.right - entityHitBox.left + 1 : 0;

		collisionDistance.y = (entityHitBox.bottom < terrainHitBox.top) ? terrainHitBox.top - entityHitBox.bottom - 1
			: (entityHitBox.top > terrainHitBox.bottom) ? terrainHitBox.bottom - entityHitBox.top + 1: 0;
		//--

		if (xCollisionTime >= 0 && xCollisionTime <= deltaTime && yCollisionTime >= 0 && yCollisionTime <= deltaTime)
		{
			if (xCollisionTime <= yCollisionTime)
				xCollisionTime = (entityHitBox.right + (velocityVector.x * yCollisionTime) < terrainHitBox.left
					|| entityHitBox.left + (velocityVector.x * yCollisionTime) > terrainHitBox.right) ? -1 : yCollisionTime
				, collisionType = (velocityVector.y > 0) ? 3 : 2;

			else
				yCollisionTime = (entityHitBox.bottom + (velocityVector.y * xCollisionTime) < terrainHitBox.top
					|| entityHitBox.top + (velocityVector.y * xCollisionTime) > terrainHitBox.bottom) ? -1 : xCollisionTime
				, collisionType = (velocityVector.x > 0) ? 1 : 0;

			if (xCollisionTime != -1 && yCollisionTime != -1)
				collisions.push_back(terrainCollision({ xCollisionTime, collisionType, collisionDistance }));
		}
	}

	for (int i = 0; i < collisions.size(); i++)
		if (collision.collisionTime == -1 || collisions.at(i).collisionTime < collision.collisionTime)
			collision = collisions.at(i);

	//Check for notGrounded if there is not already any collision
	if (collision.collisionTime == -1 && entity->GetIsGrounded() && velocityVector.x != 0)
	{
		bool groundCollision = false;

		Vector<int> checkBottomLeft = { entityHitBox.left + (int)(velocityVector.x * deltaTime), entityHitBox.bottom + 1 };
		Vector<int> checkBottomRight = { entityHitBox.right + (int)(velocityVector.x * deltaTime), entityHitBox.bottom + 1 };

		for (int i = 0; i < proximateTerrain.size() && !groundCollision; i++)
			if (IsCollision(checkBottomLeft, proximateTerrain.at(i)->GetHitBox()) || IsCollision(checkBottomRight, proximateTerrain.at(i)->GetHitBox()))
				groundCollision = true;

		if (!groundCollision)
			collision = { deltaTime, 4, Vector<int>({ (int)(velocityVector.x * deltaTime), 0 }) };
	}

	return collision;
}

bool Physics::IsCollision(Vector<int> point, RectI hitBox)
{
	if (point.x >= hitBox.left && point.x <= hitBox.right && point.y >= hitBox.top && point.y <= hitBox.bottom)
		return true;

	return false;
}

/*std::vector<PhysicalObjectPair> Physics::GetProximatePairs(std::vector<PhysicalObject*> movingPhysicalObjects, float deltaTime)
{
	std::vector<PhysicalObjectPair> proximatePairs;

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

				int objectAProximityZoneRadius = objectA->GetCloseProximityZoneRadius();
				int objectBProximityZoneRadius = objectB->GetCloseProximityZoneRadius();

				int objectAVelocityLength = objectA->GetVelocityVector().GetLength();
				int objectBVelocityLength = objectB->GetVelocityVector().GetLength();

				if (distance <= objectAProximityZoneRadius + objectBProximityZoneRadius + (objectAVelocityLength + objectBVelocityLength) * deltaTime)
				{
					proximatePairs.push_back({ objectA, objectB });
					std::cout << objectA->GetName() << " has potential to hit object:\t" << objectB->GetName() << "\tDistance: " << distance << "\n";
				}
			}
		}
	}

	return proximatePairs;
}*/

/*std::vector<Collision> Physics::GetCollisionPairs(std::vector<PhysicalObjectPair> proximatePairs)
{
	std::vector<Collision> collisions;

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

	return collisions;
}*/