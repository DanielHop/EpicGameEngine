#pragma once

#include "../../../EGE/EGE.h"

class Paddle
{
public:
	void Init(bool Player);
	void Update(float dt);

	void SetDirection(int direction);

	int GetDirection() { return mDirection; }
	Sprite GetSprite() { return mSprite; }
private:
	void Move(float dt);

	void MoveUp(float dt);
	void MoveDown(float dt);

private:
	int mDirection;
	float speed{ 0.015f };
	Sprite mSprite;
};