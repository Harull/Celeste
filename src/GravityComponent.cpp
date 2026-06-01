#include "../include/GravityComponent.h"
#include "../include/MovementComponent.h"
#include "../include/Character.h"
#include "../include/Game.h"

GravityComponent::GravityComponent(Entity* _owner, const float _gravity) : Component(_owner)
{
	gravity = _gravity;
}

void GravityComponent::Update()
{
	if (Character* _character = dynamic_cast<Character*>(owner))
		if (_character->GetIsClimbing())
			return;

	ApplyGravity();
}

void GravityComponent::ApplyGravity(const bool _reverted)
{
	if (MovementComponent* _movementComp = owner->GetComponent<MovementComponent>())
	{
		_movementComp->Move({ 0, gravity * Game::GetInstance().GetSenseOfGravity() * (_reverted ? -1 : 1)});
	}
}
