#pragma once

#include "Paddle.h"

class Player
{
public:
	void Init();
	void Update(float dt);

	void MoveUp();
	void MoveDown();
	void Stop();

	Paddle GetPaddle() { return mPaddle; }
private:
	Paddle mPaddle;
};