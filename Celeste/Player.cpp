#include "Player.h"



Player::Player()
{
	character = new Character( Vector2f(53.7f, 58.125f), Vector2f(0.0f, 0.0f), true );
	character->GetShape()->setPosition(Vector2f(500.0f, 500.0f));
}

Player::~Player()
{
	delete character;
	character = nullptr;
}

void Player::Update()
{
	character->Update();
}
