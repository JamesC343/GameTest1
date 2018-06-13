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

void Player::routine(float deltaTime)
{
	applyGravityAndFriction(deltaTime);
}

void Player::run(int xRun)
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

void Player::jump(int yJump)
{
    if(isGrounded)
		velocityVector.y += yJump;

    isGrounded = false;
}
