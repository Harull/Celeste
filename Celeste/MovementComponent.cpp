#include "MovementComponent.h"
#include "Game.h"
#include "EntityManager.h"
#include"Macro.h"

MovementComponent::MovementComponent(Entity* _owner,bool _canMove) : Component(_owner)
{
	velocity = 0.05f;
	direction = Vector2f();
	canMove = _canMove;
}

MovementComponent::MovementComponent(Entity* _owner, const float _velocity,
	const Vector2f& _direction, const bool _canMove) : Component(_owner)
{
	velocity = _velocity;
	direction = Vector2f(_direction);
	canMove = _canMove;
}

void MovementComponent::Update()
{
	Move();
	//std::cout << "x " << owner->GetShape()->getPosition().x << " | y " << owner->GetShape()->getPosition().y << std::endl;
}

void MovementComponent::Move()
{
	if (!canMove)return;

	TryToMove(owner, direction);
}

bool MovementComponent::TryToMove(Entity* _entity, const Vector2f& _direction)
{
	if (!canMove)return true;

	const Vector2f& _destination = _direction * velocity;
	_entity->GetShape()->move(_destination);

	int _collisionSideBinary = COLLIDE_NONE;
	int _entityBinary = ENTITY_NONE;
	if (CollisionComponent* _collision = _entity->GetComponent<CollisionComponent>())
	{
		if (_entityBinary = _collision->CheckCollision(_collisionSideBinary))
		{
			sf::Vector2f _newPos;
			if (_direction.x != 0 && (_collisionSideBinary & COLLIDE_LEFT || _collisionSideBinary & COLLIDE_RIGHT))
				_newPos = { -_destination.x, _newPos.y};
			if (_direction.y != 0 && _collisionSideBinary & COLLIDE_UP )
				_newPos = { _newPos.x, -_destination.y };
			if (_collisionSideBinary == COLLIDE_DOWN && _destination.y < 0)
				_newPos = { _newPos.x, -_destination.y };
			_entity->GetShape()->move(_newPos);

			return true;
		}
	}
	return false;

}

Vector2f MovementComponent::GetDirectionByPositions(Vector2f _destination)
{
	
		Vector2f _entityPos = owner->GetPosition();
		if (IsNearlyEqual(_entityPos, _destination)) return Vector2f(0.0f, 0.0f);

		const float _directionX = 0.0f;
		const float _directionY = 0.0f;
		Vector2f _direction = _destination - _entityPos;
		Normalize(_direction);
	
		return _direction;
}
