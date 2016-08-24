#pragma once

#include "Paddle.h"

class Enemy
{
public:
	void Init();
	void Update(float dt, float yBall);

	Paddle GetPaddle() { return mPaddle; }
private:
	Paddle mPaddle;

};