#include "Enemy.h"

void Enemy::Init()
{
	mPaddle.Init(false);
}

void Enemy::Update(float dt, float yBall)
{
	if (yBall > mPaddle.GetSprite().pos.y)
		mPaddle.SetDirection(1);
	else if (yBall < mPaddle.GetSprite().pos.y)
		mPaddle.SetDirection(-1);
	else
		mPaddle.SetDirection(0);

	mPaddle.Update(dt);
}