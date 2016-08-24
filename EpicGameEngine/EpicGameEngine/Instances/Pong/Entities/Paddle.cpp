#include "Paddle.h"

void Paddle::Init(bool player)
{
	mSprite.colour = { 1.0f, 1.0f, 1.0f, 1.0f };
	if(player)
		mSprite.pos = { Window::AspectRatio() - 0.05f, 0.15f / 2.f, 0.0f };
	else
		mSprite.pos = { -(Window::AspectRatio() - 0.05f), 0.15f / 2.f, 0.0f };
	mSprite.size = { 0.025f, 0.3f };
}

void Paddle::Update(float dt)
{
	Move(dt);
}

void Paddle::SetDirection(int direction)
{
	this->mDirection = direction;
}

void Paddle::Move(float dt)
{
	switch (mDirection)
	{
	case -1:
		MoveDown(dt);
		return;
	case 0:
		return;
	case 1:
		MoveUp(dt);
		return;
	}
}

void Paddle::MoveUp(float dt)
{
	if (mSprite.pos.y < 1)
		mSprite.pos = { mSprite.pos.x, mSprite.pos.y + speed , 0.0f };
}

void Paddle::MoveDown(float dt)
{
	if (mSprite.pos.y - mSprite.size.y > -1.0f)
		mSprite.pos = { mSprite.pos.x, mSprite.pos.y - speed, 0.0f };
}