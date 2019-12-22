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
	int runMax = 500 * (10);
	int run = isGrounded ? xRun : xRun / 5;

	AddForce({ (GetForceVector().x + run > runMax) ? runMax - GetForceVector().x
		: (GetForceVector().x + run < -runMax) ? -runMax - GetForceVector().x : run, 0 });
}

void Player::Jump(int yJump)
{
	if (isGrounded)
		AddForce({ 0, yJump });

    isGrounded = false;
}
