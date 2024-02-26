#include "Player.h"

Player::Player()
{
	character =  new Character(Vector2f(100.0f, 100.0f), Vector2f(0.0f, 0.0f), true);
}

void Player::Update()
{
	character->Update();
}
