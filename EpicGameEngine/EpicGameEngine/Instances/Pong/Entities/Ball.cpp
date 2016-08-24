#include "Ball.h"

void Ball::Init()
{
	mSprite.colour = { 1.0f, 1.0f, 1.0f, 1.0f };
	mSprite.pos = { 0.0f, 0.0f, 0.0f };
	mSprite.size = { 0.025f, 0.025f };

	vel = { 0.03f, -0.03f };
}

void Ball::Update(float dt)
{
	if (mSprite.pos.y > 1.0f || mSprite.pos.y - mSprite.size.y < -1.0f)
		vel.y = -vel.y;
	mSprite.pos.x += vel.x;
	mSprite.pos.y += vel.y;
}