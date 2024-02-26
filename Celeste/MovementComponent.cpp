#include "MovementComponent.h"
#include "Game.h"
#include "EntityManager.h"

MovementComponent::MovementComponent()
{
	velocity = 0.05f;
	direction = Vector2f();
	canMove = true;
}

MovementComponent::MovementComponent(const float _velocity, const Vector2f _direction, const bool _canMove)
{
	velocity = _velocity;
	direction = Vector2f(_direction);
	canMove = _canMove;
}

void MovementComponent::Move(CollisionComponent* _collision, Entity* _entity)
{
	if (!canMove)return;

	TryToMove(_collision, _entity, direction);
}

bool MovementComponent::TryToMove(CollisionComponent* _collision, Entity* _entity, const Vector2f& _direction)
{
	if (!canMove)return true;

	const Vector2f& _destination = _direction * velocity;
	_entity->GetShape()->move(_destination);

	int _collisionSideBinary = COLLIDE_NONE;
	int _entityBinary = ENTITY_NONE;
	if (_entityBinary = _collision->CheckCollision(_entity, _collisionSideBinary))
	{
		if (_direction.x != 0 && (_collisionSideBinary & COLLIDE_LEFT || _collisionSideBinary & COLLIDE_RIGHT))
			_entity->GetShape()->move(sf::Vector2f(-_destination.x, 0));
		
		return true;
	}
	return false;

}