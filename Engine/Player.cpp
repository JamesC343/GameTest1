#include "MainWindow.h"
#include "Player.h"

Player::Player(Sprite* sprite, Vei2 size, Vei2 position)
	: PhysicalObject(sprite, size, position, true)
	, Entity()
{
    //ctor
}

Player::~Player()
{
    //dtor
}

void Player::Routine(float deltaTime)
{
	ApplyGravityAndFriction(deltaTime);
}

void Player::Run(int xRun)
{
    int runMax = 300 * (20);

    if(isGrounded)
    {
		velocityVector.x += xRun;
        if (velocityVector.x < -runMax)
			velocityVector.x = -runMax;
        if (velocityVector.x > runMax)
			velocityVector.x = runMax;
    }
}

void Player::Jump(int yJump)
{
    if(isGrounded)
		velocityVector.y += yJump;

    isGrounded = false;
}
