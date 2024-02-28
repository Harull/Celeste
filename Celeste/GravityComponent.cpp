#include "GravityComponent.h"
#include "MovementComponent.h"


GravityComponent::GravityComponent(Entity* _owner, const float _gravity) : Component(_owner)
{
	gravity = _gravity;
}

void GravityComponent::Update()
{
	if (MovementComponent* _movementComp = owner->GetComponent<MovementComponent>())
	{
		sf::Vector2f _dir = _movementComp->GetDirection();
		_movementComp->SetDirection({ _dir.x, _dir.y + gravity });
	}
}
