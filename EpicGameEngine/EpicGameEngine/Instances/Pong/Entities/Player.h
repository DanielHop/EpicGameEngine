#pragma once

#include "../../../EGE/EGE.h"

class Player
{
public:
	void Init();
	void Update(float dt);

	void MoveUp();
	void MoveDown();

	Sprite GetSprite() { return mSprite; }
private:
	Sprite mSprite;
	float speed{ 0.01f };
};