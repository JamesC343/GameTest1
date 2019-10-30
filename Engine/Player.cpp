#include "MainWindow.h"
#include "Player.h"
#include <iostream>

Player::Player(Sprite* sprite, Vector<int> position, Vector<int> size, std::string name)
	: Entity(sprite, position, size, name)
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
	int run = isGrounded ? xRun : xRun / 10;

	addVelocity({ (GetVelocityVector().x + run > runMax) ? runMax - GetVelocityVector().x
		: (GetVelocityVector().x + run < -runMax) ? -runMax - GetVelocityVector().x : run, 0 });
}

void Player::Jump(int yJump)
{
	if (isGrounded)
		addVelocity({ 0, yJump });

    isGrounded = false;
}
