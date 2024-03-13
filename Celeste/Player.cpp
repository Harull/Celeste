#include "Player.h"
#include "MovementComponent.h"
#include "EventReactionManager.h"

Player::Player()
{
	character = new Character({ 1920.f / 40.f - 5.f, 1080.f / 22.5f * 2.f - 5.f}, { 200.f, 50.f }, 15, true);
	InitInput();
}


void Player::InitInput()
{
	EventReactionManager::BindNewInputReaction(sf::Event::KeyPressed, [&](const sf::Event& _event) {return character->MovingLeftRight(_event); });
	EventReactionManager::BindNewInputReaction(sf::Event::KeyReleased, [&](const sf::Event& _event) {return character->MovingLeftRight(_event); });
	EventReactionManager::BindNewInputReaction(sf::Event::JoystickMoved, [&](const sf::Event& _event) {return character->MovingLeftRight(_event); });

	EventReactionManager::BindNewInputReaction(sf::Event::KeyPressed, [&](const sf::Event& _event) {return character->Climb(_event); });
	EventReactionManager::BindNewInputReaction(sf::Event::KeyReleased, [&](const sf::Event& _event) {return character->Climb(_event); });
	EventReactionManager::BindNewInputReaction(sf::Event::JoystickMoved, [&](const sf::Event& _event) {return character->Climb(_event); });

	EventReactionManager::BindNewInputReaction(sf::Event::KeyPressed, [&](const sf::Event& _event) {return character->Jump(_event); });
	EventReactionManager::BindNewInputReaction(sf::Event::JoystickButtonPressed, [&](const sf::Event& _event) {return character->Jump(_event); });

	EventReactionManager::BindNewInputReaction(sf::Event::KeyPressed, [&](const sf::Event& _event) {return character->Dash(_event); });
	EventReactionManager::BindNewInputReaction(sf::Event::JoystickButtonPressed, [&](const sf::Event& _event) {return character->Dash(_event); });
}

void Player::Update()
{
	character->Update();
}
