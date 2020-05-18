#include "Physics.h"

Physics::Physics(Player* target, TerrainMap* terrainMap, std::vector<TerrainObject*>* terrainObjects, std::vector<Entity*>* entities)
	: target (target), terrainMap(terrainMap), terrainObjects(terrainObjects), entities(entities)
{
    //ctor
}

Physics::~Physics()
{
    //dtor
}

void Physics::Routine(float deltaTime)
{
	std::vector<Entity*> movingEntities = GetMovingEntities();

	for (int i = 0; i < movingEntities.size(); i++)
	{
		Entity* entity = movingEntities.at(i);

		Vector<int> currentPosition = entity->GetHitBox().GetBottomCenter();
		Vector<int> newPosition = entity->GetHitBox(deltaTime).GetBottomCenter();

		if (movingEntities.at(i)->GetIsGrounded())//WalkingPhysics
			entity->Move(GetWalkTarget(entity, deltaTime));

		else//TrajectoryPhysics
		{
			if (!terrainMap->ValidPosition(newPosition))
			{
				int precision = 7;
				int fractionSize = std::pow(2, precision);
				int deltaTimeFraction = fractionSize / 2;

				Vector<int> positionA;

				for (int i = 0; i < precision; i++)
				{
					positionA = entity->GetHitBox(deltaTime / fractionSize * deltaTimeFraction).GetBottomCenter();

					if (!terrainMap->ValidPosition(positionA))
						deltaTimeFraction -= fractionSize / std::pow(2, i + 2);

					else
					{
						newPosition = entity->GetHitBox(deltaTime / fractionSize * deltaTimeFraction).GetBottomCenter();
						deltaTimeFraction += fractionSize / std::pow(2, i + 2);
					}
				}

				entity->Move(deltaTime / fractionSize * deltaTimeFraction);
			}
			else
				entity->Move(deltaTime);

			//Need new Physics.IsCollision() to check player aginst TerrainMap and all PhysicalObjects (version 0.1)
			//How do I calculate the PixelOverlap of a result of the collision?
			if (terrainMap->IsCollision(newPosition))
			{
				entity->SetGrounded(true);
			}

			CollisionOverlap(target);
		}




		//Previous version prior to PixelOverlapPhysics version 0.1
		/*{
			if (terrainMap->IsCollision(newPosition) || !terrainMap->ValidPosition(newPosition))
			{//One thing to remember, this is utilizing the "terrainMap" physics which operates at a pixel level (just for the terrain)
			//This is suitable for a basic start and later on I can choose to develop 2D model physics for the terrain as well
			//The idea is to use a different model for collisions between moving objects
				int precision = 7;
				int fractionSize = std::pow(2, precision);
				int deltaTimeFraction = fractionSize / 2;

				Vector<int> positionA;

				for (int i = 0; i < precision; i++)
				{
					positionA = entity->GetHitBox(deltaTime / fractionSize * deltaTimeFraction).GetBottomCenter();

					if (terrainMap->IsCollision(positionA) || !terrainMap->ValidPosition(positionA))
						deltaTimeFraction -= fractionSize / std::pow(2 , i + 2);

					else
					{
						newPosition = entity->GetHitBox(deltaTime / fractionSize * deltaTimeFraction).GetBottomCenter();
						deltaTimeFraction += fractionSize / std::pow(2, i + 2);
					}
				}

				entity->Move(deltaTime / fractionSize * deltaTimeFraction);
				entity->SetGrounded(true);//This doesnt really make sense, the current system sets back to 'not grounded' as part of Jump()
				//Currently jumping into a wall sets grounded
				std::cout << "Collision" << "\n";
			}
			else
				entity->Move(deltaTime);
		}*/
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

Vector<int> Physics::GetWalkTarget(Entity* entity, float deltaTime)
{
	Vector<int> currentPosition = entity->GetHitBox().GetBottomCenter();
	int xLength = entity->GetVelocityVector().x * deltaTime;
	int xDirection = xLength > 0 ? 1 : -1;

	//This is a reference for the maximum allowed distance to be travelled, distanceSq is more efficient for 2D Vectors
	int distanceSq = entity->GetVelocityVector().GetLengthSq() * deltaTime;

	int xMove, yMove;
	for (int i = abs(xLength); i >= 0; i--)
	{
		xMove = i * xDirection;

		if (terrainMap->ValidPosition({ currentPosition.x + xMove, currentPosition.y }))
		{
			yMove = terrainMap->GetY( currentPosition.x + xMove ) - currentPosition.y;

			//It is possible to move futher than the maximum allowed distance if yMove is large enough
			if (distanceSq >= (Vector<int>({ xMove, yMove })).GetLengthSq())
				return { xMove, yMove };
		}
	}

	return { 0, 0 };
}

bool Physics::IsCollision(Vector<int> point, RectI hitBox)
{
	if (point.x >= hitBox.left && point.x <= hitBox.right && point.y >= hitBox.top && point.y <= hitBox.bottom)
		return true;

	return false;
}

Vector<int> Physics::CollisionOverlap(Player* player)//version 0.1
{	//Returns count of 1 for each pixel that is overlapped
	int totalPixelOverlapCount = 0;
	int playerExternalPixelOverlapCount = 0;
	int objectExternalPixelOverlapCount = 0;

	TerrainObject* object = terrainObjects->at(1);

	RectI playerHitbox = player->GetHitBox();
	RectI objectHitbox = object->GetHitBox();

	//collisionMinX = the larger of the 2 MinX (.left) values
	//collisionMaxX = the smaller of the 2 MaxX (.right) values
	int overlapMinX = playerHitbox.left > objectHitbox.left ? playerHitbox.left : objectHitbox.left;
	int overlapMaxX = playerHitbox.right < objectHitbox.right ? playerHitbox.right : objectHitbox.right;

	if (overlapMaxX - overlapMinX + 1 > 0)
	{
		//For use in determining the collision 'corners'
		int collisionMinIndex = -1;
		int collisionMaxIndex = -1;
		
		int* collisionMinY = new int[overlapMaxX - overlapMinX + 1];
		int* collisionMaxY = new int[overlapMaxX - overlapMinX + 1];

		for (int i = overlapMinX, collisionIndex = 0; i <= overlapMaxX; i++, collisionIndex++)
		{
			//i is the x value on the map/world
			//The player/object x and y values are on their hitbox
			int playerMinYAtX = player->GetMinY(i - playerHitbox.left) + playerHitbox.top;
			int objectMinYAtX = object->GetMinY(i - objectHitbox.left) + objectHitbox.top;
			int playerMaxYAtX = player->GetMaxY(i - playerHitbox.left) + playerHitbox.top;
			int objectMaxYAtX = object->GetMaxY(i - objectHitbox.left) + objectHitbox.top;

			//overlapYMin = the larger of the 2 MinY values
			//overlapYMax = the smaller of the 2 MaxY values
			int minY = collisionMinY[collisionIndex] = playerMinYAtX > objectMinYAtX ? playerMinYAtX : objectMinYAtX;
			int maxY = collisionMaxY[collisionIndex] = playerMaxYAtX < objectMaxYAtX ? playerMaxYAtX : objectMaxYAtX;

			int collisionYOverlap = maxY - minY + 1;

			if (collisionYOverlap > 0)
			{
				//This part is simply and counts the total number of pixels overlapped
				totalPixelOverlapCount += collisionYOverlap;

				if (collisionMinIndex == -1)
					collisionMinIndex = collisionIndex;

				collisionMaxIndex = collisionIndex;

				//Here on is a bit more complicated and counts playerExternalPixelOverlapCount and objectExternalPixelOverlapCount
				//First based on if the current value of i lines up with the players (or Objects) min or max X value (every pixel at min or max x is external)
				//Else based on if the min or max y value is part of the overlap
				if (i == playerHitbox.left || i == playerHitbox.right)
					playerExternalPixelOverlapCount += collisionYOverlap;

				else
				{
					if (playerMinYAtX == minY)
						playerExternalPixelOverlapCount++;

					if (playerMaxYAtX == maxY)
						playerExternalPixelOverlapCount++;
				}

				if (i == objectHitbox.left || i == objectHitbox.right)
					objectExternalPixelOverlapCount += collisionYOverlap;

				else
				{
					if (objectMinYAtX == minY)
						objectExternalPixelOverlapCount++;

					if (objectMaxYAtX == maxY)
						objectExternalPixelOverlapCount++;
				}
			}
		}

		if (totalPixelOverlapCount > 0)
		{
			Vector<float> relativeVelocity = Vector<float>(0, 0) - player->GetVelocityVector();

			int massA = player->GetWeight();
			int massB = 3;//object->GetWeight();

			//These variables are from the perspective of ObjectA (Player in this case)
			//Inverted is refering to the angle directly behind ObjectA when looking at ObjectB
			Vector<float> objectDistanceVector = objectHitbox.GetCenter() - playerHitbox.GetCenter();
			Vector<float> invertedObjectAngleVector = objectDistanceVector * -1 / objectDistanceVector.GetLength();//Standardizes to length = 1

			float baseAngleScale = (invertedObjectAngleVector.x >= 0) ? 1 + invertedObjectAngleVector.y : 3 - invertedObjectAngleVector.y;
			Vector<float> collisionInnerPixel = { -1, -1 };
			Vector<float> collisionOuterPixel = { -1, -1 };

			//For use in determining the collisionInnerPixel and collisionOuterPixel
			float collisionMinAngleScale = -1, collisionMaxAngleScale = -1;
			for (int i = 0; i < 2; i++)
			{
				int collisionIndex = (i == 0) ? collisionMinIndex : collisionMaxIndex;
				for (int j = 0; j < 2; j++)
				{
					Vector<int> pixel = { overlapMinX + collisionIndex, (j == 0) ? collisionMinY[collisionIndex] : collisionMaxY[collisionIndex] };
					Vector<float> pixelDistanceVector = playerHitbox.GetCenter() - pixel;
					Vector<float> pixelAngleVector = pixelDistanceVector / pixelDistanceVector.GetLength();

					float pixelAngleScale = (pixelAngleVector.x >= 0) ? 1 + pixelAngleVector.y : 3 - pixelAngleVector.y;
					float pixelRelativeAngleScale = pixelAngleScale - baseAngleScale;
					pixelRelativeAngleScale += pixelRelativeAngleScale < 0 ? 4 : 0;//Normalize to a scale from 0 to 4

					if (pixelRelativeAngleScale < collisionMinAngleScale || collisionMinAngleScale == -1)
						collisionMinAngleScale = pixelRelativeAngleScale,
						collisionInnerPixel = pixel;
					else if (pixelRelativeAngleScale > collisionMaxAngleScale)
						collisionMaxAngleScale = pixelRelativeAngleScale,
						collisionOuterPixel = pixel;
				}
			}
			
			//1. Currently taking the average of the inner and outer pixels and then getting the angle relative from ObjectA means that the bahaviour is not hugely different from the first vesion
				//(First version taking the angle relative from OjectA to ObjectB)
			//2. The angle will need to be determined from collisionInnerPixel to collisionOuterPixel and then rotated clockwise(?) 90 degrees
				//However this will still not be perfect when there is a very small overlap
				//Possibly: A. this can be fixed by reverting to the 'current' implementation when the totalPixelOverlapCount is below a threshold
					//OR use relative velocity as the collisionAngleVector ... even further this could be combined with solution (2.) at a ratio determined by the totalPixelOverlapCount
				//or B. this will be insignificant once the maximum force per 'PixelOverlap' system is in place	(Still could be an issue if the 'maximum force per 'PixelOverlap' is really high for a pair of objects
			//(?)Note. Will 'maximum force per 'PixelOverlap' be determined in a similar way to how mass is factored into the force calculation?

			//The collisionAngleVector affects the amount of momentum absorbed into the collision for each dimension
				//The total energy for each dimension is added together
			Vector<float> collisionDistanceVector = ((collisionInnerPixel + collisionOuterPixel) / 2) - playerHitbox.GetCenter();
			Vector<float> collisionAngleVector = collisionDistanceVector * -1 / collisionDistanceVector.GetLength();//Standardizes to length = 1
			
			//The formula I have played with that works is : RelativeVelocity x massA x massB x 2 / massA + massB
				//This gives the total energy to be applied to each object in the collision
			float collisionEnergy = (relativeVelocity.x * collisionAngleVector.x + relativeVelocity.y * collisionAngleVector.y) * massA * massB * 2 / (massA + massB);

			//The collisionAngleVectorRatio is then again used for the output distrubution of that total energy to each dimension
				//Negative relativeVelocity multiplied by negative collisionAngleVectorRatio gives a positive force, in this case I want that to be a negative force (I could reverse the order for the relativeVelocity calculation above)
				//This means that a negative energy for the X dimension has the potential to reduce the energy from the Y dimension, however a total negative value will be ignored
			Vector<float> outputEnergyVector = collisionAngleVector * collisionEnergy;

			//If collisionEnergy were a negative value, it would suck the objects back together, this occurs during the part of the collision where the overlap is still present but the objects are moving away from each other
			if (collisionEnergy > 0)//Should be AddVelocity, however the Force-Velocity concept is not in place yet
				player->AddForce(outputEnergyVector / (massA > 0 ? massA : 1));//Protect against divide by zero
		}
	}

	//Ignore the return value for now
	//Make sure that it is not being used
	return { 0, -totalPixelOverlapCount };
}

//void Physics::RoutineLegacy(float deltaTime)//Isn't it funny how an x collision causes y distance to be reduced? This applies to both jumping up and also falling back down
//{
//	std::vector<Entity*> movingEntities = GetMovingEntities();
//	
//	for (int i = 0; i < movingEntities.size(); i++)
//	{
//		Entity* entity = movingEntities.at(i);
//		float elapsedDeltaTime = 0;
//
//		while (elapsedDeltaTime < deltaTime)
//		{
//			std::vector<TerrainObject*> proximateTerrain = GetProximateTerrain(entity, deltaTime - elapsedDeltaTime);
//			terrainCollision nextCollision = GetNextTerrainCollision(entity, proximateTerrain, deltaTime - elapsedDeltaTime);
//			if (nextCollision.collisionTime != -1)
//			{
//				assert(nextCollision.collisionTime != 0);
//				elapsedDeltaTime += nextCollision.collisionTime;
//
//				entity->Move(nextCollision.distance);
//				
//				switch (nextCollision.collisionType)
//				{//0,1,2,3 - left,right,up,down
//				case 0:
//					entity->SetXCollision();
//					break;
//				case 1:
//					entity->SetXCollision();
//					break;
//				case 2:
//					entity->SetYCollision();
//					break;
//				case 3:
//					//std::cout << "SetGrounded True\n";
//					entity->SetGrounded(true);
//					break;
//				case 4:
//					//std::cout << "SetGrounded False\n";
//					entity->SetGrounded(false);
//					break;
//				}
//			}
//			else
//				entity->Move(deltaTime - elapsedDeltaTime), elapsedDeltaTime = deltaTime;
//		}
//	}
//}

//std::vector<TerrainObject*> Physics::GetProximateTerrain(Entity* entity, float deltaTime)
//{
//	std::vector<TerrainObject*> proximateTerrain;
//	TerrainObject* terrain;
//
//	int entityVelocityLength = entity->GetVelocityVector().GetLength() * deltaTime;
//
//	for (int j = 0; j < terrainObjects->size(); j++)
//	{
//		terrain = terrainObjects->at(j);
//
//		int distance = (entity->GetHitBox().GetCenter() - terrain->GetHitBox().GetCenter()).GetLength();
//
//		if (distance <= entity->GetCloseProximityZoneRadius() + terrain->GetCloseProximityZoneRadius() + entityVelocityLength)
//			proximateTerrain.push_back(terrain);
//	}
//
//	return proximateTerrain;
//}

//terrainCollision Physics::GetNextTerrainCollision(Entity* entity, std::vector<TerrainObject*> proximateTerrain, float deltaTime)
//{
//	terrainCollision collision;
//	std::vector<terrainCollision> collisions;
//
//	RectI entityHitBox = entity->GetHitBox();
//	Vector<float> velocityVector = entity->GetVelocityVector();
//
//	PhysicalObject* terrain;
//	RectI terrainHitBox;
//
//	float xCollisionTime = -1;
//	float yCollisionTime = -1;
//	Vector<int> collisionDistance = { 0,0 };
//	int collisionType = -1;
//	
//	//Check for collisions
//	for (int i = 0; i < proximateTerrain.size(); i++)
//	{
//		terrain = proximateTerrain.at(i);
//		terrainHitBox = terrain->GetHitBox();
//
//		assert(!(entityHitBox.right >= terrainHitBox.left && entityHitBox.left <= terrainHitBox.right && entityHitBox.bottom >= terrainHitBox.top && entityHitBox.top <= terrainHitBox.bottom));
//
//		xCollisionTime = ((entityHitBox.right < terrainHitBox.left || entityHitBox.left > terrainHitBox.right) && velocityVector.x == 0) ? -1
//			: (entityHitBox.right < terrainHitBox.left) ? (terrainHitBox.left - entityHitBox.right) / velocityVector.x
//			: (entityHitBox.left > terrainHitBox.right) ? (terrainHitBox.right - entityHitBox.left) / velocityVector.x : 0;
//
//		yCollisionTime = ((entityHitBox.bottom < terrainHitBox.top || entityHitBox.top > terrainHitBox.bottom) && velocityVector.y == 0) ? -1
//			: (entityHitBox.bottom < terrainHitBox.top) ? (terrainHitBox.top - entityHitBox.bottom) / velocityVector.y
//			: (entityHitBox.top > terrainHitBox.bottom) ? (terrainHitBox.bottom - entityHitBox.top) / velocityVector.y : 0;
//
//		//--Now that Physics moves objects by distance specifically instead of time, could consider to re-simplify this function
//		collisionDistance.x = (entityHitBox.right < terrainHitBox.left) ? terrainHitBox.left - entityHitBox.right - 1
//			: (entityHitBox.left > terrainHitBox.right) ? terrainHitBox.right - entityHitBox.left + 1 : 0;
//
//		collisionDistance.y = (entityHitBox.bottom < terrainHitBox.top) ? terrainHitBox.top - entityHitBox.bottom - 1
//			: (entityHitBox.top > terrainHitBox.bottom) ? terrainHitBox.bottom - entityHitBox.top + 1: 0;
//		//--
//
//		if (xCollisionTime >= 0 && xCollisionTime <= deltaTime && yCollisionTime >= 0 && yCollisionTime <= deltaTime)
//		{
//			if (xCollisionTime <= yCollisionTime)
//				xCollisionTime = (entityHitBox.right + (velocityVector.x * yCollisionTime) < terrainHitBox.left
//					|| entityHitBox.left + (velocityVector.x * yCollisionTime) > terrainHitBox.right) ? -1 : yCollisionTime
//				, collisionType = (velocityVector.y > 0) ? 3 : 2;
//
//			else
//				yCollisionTime = (entityHitBox.bottom + (velocityVector.y * xCollisionTime) < terrainHitBox.top
//					|| entityHitBox.top + (velocityVector.y * xCollisionTime) > terrainHitBox.bottom) ? -1 : xCollisionTime
//				, collisionType = (velocityVector.x > 0) ? 1 : 0;
//
//			if (xCollisionTime != -1 && yCollisionTime != -1)
//				collisions.push_back(terrainCollision({ xCollisionTime, collisionType, collisionDistance }));
//		}
//	}
//
//	for (int i = 0; i < collisions.size(); i++)
//		if (collision.collisionTime == -1 || collisions.at(i).collisionTime < collision.collisionTime)
//			collision = collisions.at(i);
//
//	//Check for notGrounded if there is not already any collision
//	if (collision.collisionTime == -1 && entity->GetIsGrounded() && velocityVector.x != 0)
//	{
//		bool groundCollision = false;
//
//		Vector<int> checkBottomLeft = { entityHitBox.left + (int)(velocityVector.x * deltaTime), entityHitBox.bottom + 1 };
//		Vector<int> checkBottomRight = { entityHitBox.right + (int)(velocityVector.x * deltaTime), entityHitBox.bottom + 1 };
//
//		for (int i = 0; i < proximateTerrain.size() && !groundCollision; i++)
//			if (IsCollision(checkBottomLeft, proximateTerrain.at(i)->GetHitBox()) || IsCollision(checkBottomRight, proximateTerrain.at(i)->GetHitBox()))
//				groundCollision = true;
//
//		if (!groundCollision)
//			collision = { deltaTime, 4, Vector<int>({ (int)(velocityVector.x * deltaTime), 0 }) };
//	}
//
//	return collision;
//}

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