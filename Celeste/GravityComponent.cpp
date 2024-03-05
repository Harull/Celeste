#include "GravityComponent.h"
#include "MovementComponent.h"
#include "Character.h"
#include "Game.h"

GravityComponent::GravityComponent(Entity* _owner, const float _gravity) : Component(_owner)
{
	gravity = _gravity;
}

void GravityComponent::Update()
{
	if (Character* _character = dynamic_cast<Character*>(owner))
		if (_character->GetIsClimbing())
			return;

	if (MovementComponent* _movementComp = owner->GetComponent<MovementComponent>())
	{
		sf::Vector2f _dir = _movementComp->GetDirection();
		_movementComp->Move({ 0, gravity * Game::GetInstance().GetSenseOfGravity()});
	}
}
