#include "Player.h"

void Player::Init()
{
	mPaddle.Init(true);
}

void Player::Update(float dt)
{
	mPaddle.Update(dt);
}

void Player::MoveUp()
{
	mPaddle.SetDirection(1);
}

void Player::MoveDown()
{
	mPaddle.SetDirection(-1);
}

void Player::Stop()
{
	mPaddle.SetDirection(0);
}