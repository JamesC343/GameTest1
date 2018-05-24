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
	applyGravityAndFriction(deltaTime);
}

void Player::run(int xRun)
{
    int runMax = 300;

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
