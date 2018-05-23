#include "MainWindow.h"
#include "EntityY.h"
#include "time.h"

EntityY::EntityY(std::string spritePath, RectI rect, Vei2 size, Vei2 position)
	: Entity(spritePath, rect, size, position)
{
    //ctor
	srand (time(NULL));
}

EntityY::~EntityY()
{
    //dtor
}

void EntityY::routine(float DeltaTime)
{
    //Gravity
    yVelocity += 10;

    //Friction
    if(xVelocity > 0)
        xVelocity--;
    else if(xVelocity < 0)
        xVelocity++;

	decisionMaking();
}

void EntityY::decisionMaking()
{
	//if idle choose random case
	//use a clock and a time for a previously selected case to identify if idle or not
	int randomNumber = rand() % 10;
	int decision = randomNumber / 3;

	switch (decision)
	{
	case 0://Jump once or twice
		jump(-10 * (randomNumber % 3 + 1));
	
	case 1://Walk towards player
		return;
	
	case 2://Walk random direction
		run(randomNumber * ((randomNumber % 3) - 1));
	
	default://Wait for a few seconds
		return;
	}
}

void EntityY::run(int xRun)
{
    int runMax = 20;

    if(isGrounded)
    {
        xVelocity += xRun;
        if (xVelocity < -runMax)
            xVelocity = -runMax;
        if (xVelocity > runMax)
            xVelocity = runMax;
    }
}

void EntityY::jump(int yJump)
{
    if(isGrounded)
        yVelocity += yJump;

    isGrounded = false;
}
