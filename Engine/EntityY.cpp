#include "MainWindow.h"
#include "EntityY.h"
#include "time.h"

EntityY::EntityY(Sprite* sprite, Vei2 position, Vei2 size)
	: PhysicalObject(sprite, position, size, true)
	, Entity()
{
    //ctor
	srand (time(NULL));
}

EntityY::~EntityY()
{
    //dtor
}

void EntityY::Routine(float deltaTime)
{
	ApplyGravityAndFriction(deltaTime);

	DecisionMaking();
}

void EntityY::DecisionMaking()
{
	//if idle choose random case
	//use a clock and a time for a previously selected case to identify if idle or not
	int randomNumber = rand() % 9;
	int decision = randomNumber / 3;

	switch (decision)
	{
	case 0://Jump once or twice
		Jump(-100 * (randomNumber % 3 + 1));
	
	case 1://Walk towards player
		return;
	
	case 2://Walk random direction
		Run(randomNumber * ((randomNumber % 3) - 1) * 10);
	
	default://Wait for a few seconds
		return;
	}
}

void EntityY::Run(int xRun)
{
    int runMax = 150;

    if(isGrounded)
    {
		velocityVector.x += xRun;
        if (velocityVector.x < -runMax)
			velocityVector.x = -runMax;
        if (velocityVector.x > runMax)
			velocityVector.x = runMax;
    }
}

void EntityY::Jump(int yJump)
{
    if(isGrounded)
		velocityVector.y += yJump;

    isGrounded = false;
}
