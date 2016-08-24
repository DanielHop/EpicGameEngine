#pragma once

#include "EGE.h"

class Ball
{
public:
	void Init();
	void Update(float dt);
	
	Sprite GetSprite() { return mSprite; }

	void SetVel(Vec2f vel) { this->vel = vel; }
	void FlipVel(Vec2f f) { vel.x *= f.x; vel.y *= f.y; }
private:
	Sprite mSprite;
	Vec2f vel;
};