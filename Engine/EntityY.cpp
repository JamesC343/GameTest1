#include "MainWindow.h"
#include "EntityY.h"
#include "time.h"

EntityY::EntityY(Sprite* sprite, Vector<int> position, Vector<int> size, std::string name)
	: Entity(sprite, position, size, name)
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
		Jump(-200 * (randomNumber % 3 + 1));
	
	case 1://Walk towards player
		return;
	
	case 2://Walk random direction
		Run(randomNumber * ((randomNumber % 3) - 1) * 100);
	
	default://Wait for a few seconds
		return;
	}
}

void EntityY::Run(int xRun)
{
	int runMax = 150;
	int run = isGrounded ? xRun : xRun / 5;

	AddForce({ (GetForceVector().x + run > runMax) ? runMax - GetForceVector().x
		: (GetForceVector().x + run < -runMax) ? -runMax - GetForceVector().x : run, 0 });
}

void EntityY::Jump(int yJump)
{
    if(isGrounded)
		AddForce({ 0, yJump });

    isGrounded = false;
}
