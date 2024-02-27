#include "Player.h"
#include "MovementComponent.h"
#include "EventReactionManager.h"

Player::Player()
{
	character = new Character({ 20.f, 25.f }, { 0.f, 0.f }, true);
	InitInput();
}

Player::~Player()
{
	delete character;
	character = nullptr;
}

void Player::InitInput()
{
	EventReactionManager::BindNewInputReaction(sf::Event::KeyPressed, [&](const sf::Event& _event) {return character->MovingLeftRight(_event); });
	EventReactionManager::BindNewInputReaction(sf::Event::KeyReleased, [&](const sf::Event& _event) {return character->MovingLeftRight(_event); });
}

void Player::Update()
{
	character->Update();
}
