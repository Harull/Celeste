#include "Player.h"
#include "MovementComponent.h"
#include "EventReactionManager.h"




Player::Player()
{
	character = new Character({ 1920.f / 40.f * 1.25f, 1080.f / 22.5f * 2.5f}, { 200.f, 50.f }, 5, true);
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
	EventReactionManager::BindNewInputReaction(sf::Event::KeyPressed, [&](const sf::Event& _event) {return character->Jump(_event); });
}

void Player::Update()
{
	character->Update();
}
