#include "MainWindow.h"
#include "Player.h"

Player::Player(std::string spritePath, RectI rect, Vei2 size, Vei2 position)
	: Entity(spritePath, rect, size, position)
{
    //ctor
}

Player::~Player()
{
    //dtor
}

void Player::routine(float deltaTime)
{
	int frictionFactor = 5;

	if (isGrounded)
		frictionFactor = 20;

    //Gravity
	yVelocity += 1000 * deltaTime;

    //Friction
	if (xVelocity > frictionFactor)
		xVelocity -= frictionFactor;
	else if (xVelocity < -frictionFactor)
		xVelocity += frictionFactor;
	else
		xVelocity = 0;
}

void Player::run(int xRun)
{
    int runMax = 300;

    if(isGrounded)
    {
        xVelocity += xRun;
        if (xVelocity < -runMax)
			xVelocity = -runMax;
        if (xVelocity > runMax)
			xVelocity = runMax;
    }
}

void Player::jump(int yJump)
{
    if(isGrounded)
        yVelocity += yJump;

    isGrounded = false;
}
