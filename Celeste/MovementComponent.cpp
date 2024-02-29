#include "MovementComponent.h"
#include "Game.h"
#include "EntityManager.h"
#include "TimerManager.h"

MovementComponent::MovementComponent(Entity* _owner) : Component(_owner)
{
	velocity = 0.05f;
	direction = Vector2f();
	canMove = true;
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

	const Vector2f& _destination = { _direction.x * velocity, _direction.y };
	_entity->GetShape()->move(_destination);

	if (CollisionComponent* _collision = _entity->GetComponent<CollisionComponent>())
	{
		CollisionInfos _collisionInfos = _collision->CheckCollision();
		//std::cout << _collisionInfos.smallestXOverlap << " | " << _collisionInfos.smallestYOverlap << std::endl;
		int _collisionSideBinary = _collisionInfos.collisionSideBinary;
		if (_collisionSideBinary)
		{
			sf::Vector2f _newPos;

			if (_direction.x != 0 && (_collisionSideBinary & COLLIDE_RIGHT))
				_newPos = { _collisionInfos.smallestXOverlap - 0.1f, _newPos.y};
			if (_direction.x != 0 && (_collisionSideBinary & COLLIDE_LEFT))
				_newPos = { -_collisionInfos.smallestXOverlap + 0.1f, _newPos.y };
			if (_direction.y != 0 && _collisionSideBinary & COLLIDE_UP)
			{
				_newPos = { _newPos.x, -_collisionInfos.smallestYOverlap + 0.1f };
				if (Character* _character = dynamic_cast<Character*>(_entity))
				{
					try
					{
						if (_character->GetCurrentJumpTimerIndex() < 1) throw exception();
						_character->SetIsJumping(false);
						Timer* _jumpTimer = TimerManager::GetInstance().GetApproximately("JumpTimer");
						if (_jumpTimer)
							_jumpTimer->Stop();
					}
					catch (const std::exception&){}
				}
			}

			if ((_collisionSideBinary & COLLIDE_DOWN) && _destination.y < 0)
				_newPos = { _newPos.x, -_destination.y };
			_entity->GetShape()->move(_newPos);

			return true;
		}
	}
	return false;

}