#include "Player.h"

void Player::Init()
{
	mSprite.colour = { 1.0f, 1.0f, 1.0f, 1.0f };
	mSprite.pos = { 0.5f, 0.15f / 2.f, 1.0f };
	mSprite.size = { 0.025f, 0.15f };
	mSprite.rot = 0;
}

void Player::Update(float dt)
{

}

void Player::MoveUp()
{
	mSprite.pos = { mSprite.pos.x, mSprite.pos.y + speed, 1.0f };
}

void Player::MoveDown()
{
	mSprite.pos = { mSprite.pos.x, mSprite.pos.y - speed, 1.0f };
}