#include "MovementComponent.h"
#include "Game.h"
#include "EntityManager.h"

#include "TimerManager.h"
#include "Character.h"

#include"Macro.h"


MovementComponent::MovementComponent(Entity* _owner,bool _canMove,bool _freeMovement) : Component(_owner)
{
	velocity = 0.5f;
	direction = Vector2f();
	canMove = _canMove;
	freeMovement = _freeMovement;
}

MovementComponent::MovementComponent(Entity* _owner, const float _velocity,
	const Vector2f& _direction, const bool _canMove, bool _freeMovement) : Component(_owner)
{
	velocity = _velocity;
	direction = Vector2f(_direction);
	canMove = _canMove;
	freeMovement = _freeMovement;
}

//TODO le bouger de là, le mettre dans character
void MovementComponent::UpdateAnimations()
{
	if (Character* _character = dynamic_cast<Character*>(owner))
	{
		CollisionInfos _collisionInfos = _character->GetComponent<CollisionComponent>()->CheckCollision();
		if (AnimationComponent* _anim = owner->GetComponent<AnimationComponent>())
		{
			AnimationDirection _adirection;
			const bool _characterIsJumping = _character->GetIsJumping();
			const bool _characterIsClimbing = _character->GetIsClimbing();
			const bool _characterIsDashing = _character->GetIsDashing();

			if (_characterIsClimbing)
			{
				CollisionInfos _collisionInfosOnWalls = _character->GetComponent<CollisionComponent>()->CheckCollision(true);

				if (direction.y > 0 || direction.y < 0)
					_adirection = _collisionInfosOnWalls.collisionSideBinary & COLLIDE_RIGHT ? ANIM_DIR_CLIMB_LEFT : ANIM_DIR_CLIMB_RIGHT;
				else
					_adirection = _collisionInfosOnWalls.collisionSideBinary & COLLIDE_RIGHT ? ANIM_DIR_GRAB_LEFT : ANIM_DIR_GRAB_RIGHT;
			}
			else if (direction.x > 0)
			{
				if (_characterIsDashing)
					_adirection = ANIM_DIR_DASH_RIGHT;
				else if (_characterIsJumping)
					_adirection = ANIM_DIR_JUMP_RIGHT;
				else if (!(_collisionInfos.collisionSideBinary == COLLIDE_UP) && !_characterIsJumping)
					_adirection = ANIM_DIR_FALL_RIGHT;
				else
					_adirection = ANIM_DIR_RIGHT;
			}
			else if (direction.x < 0)
			{
				if (_characterIsDashing)
					_adirection = ANIM_DIR_DASH_LEFT;
				else if (_characterIsJumping)
					_adirection = ANIM_DIR_JUMP_LEFT;
				else if (!(_collisionInfos.collisionSideBinary == COLLIDE_UP) && !_characterIsJumping)
					_adirection = ANIM_DIR_FALL_LEFT;
				else
					_adirection = ANIM_DIR_LEFT;
			}
			else
			{
				if (_characterIsDashing)
					_adirection = ANIM_DIR_DASH_RIGHT;
				else if (_characterIsJumping)
					_adirection = ANIM_DIR_JUMP_RIGHT;
				
				else
					_adirection = ANIM_DIR_NONE;
			}
			_anim->SetDirection(_adirection);
		}
	}


}

void MovementComponent::Update()
{
	Move();
	//std::cout << "x " << owner->GetShape()->getPosition().x << " | y " << owner->GetShape()->getPosition().y << std::endl;
}

void MovementComponent::Move(const sf::Vector2f& _direction, const bool _applyVelocity)
{
	if (!canMove)return;
	TryToMove(owner, _direction, _applyVelocity);
	UpdateAnimations();
}

void MovementComponent::Move(const bool _applyVelocity)
{
	if (!canMove)return;
	UpdateAnimations();
	TryToMove(owner, direction, _applyVelocity);
}


bool MovementComponent::TryToMove(Entity* _entity, const Vector2f& _direction, const bool _applyVelocity)
{
	if (!canMove)return true;

	Vector2f _destination = freeMovement ? Vector2f(_direction.x * velocity, _direction.y * velocity) : Vector2f(_direction.x * velocity, _direction.y);
	if (!_applyVelocity)
		_destination = _direction;
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
					if (_character->GetCurrentJumpTimerIndex() > 1)
					{
						_character->SetIsJumping(false);
						if (Timer* _jumpTimer = TimerManager::GetInstance().GetApproximately("JumpTimer"))
							_jumpTimer->Stop();
					}
				}
			}

			if (Character* _character = dynamic_cast<Character*>(_entity))
			{
				Timer* _dashTimer = TimerManager::GetInstance().GetApproximately("DashTimer");
				if (_character->GetCurrentDashTimerIndex() > 10)
				{
					if (_dashTimer)
						_dashTimer->Stop();	
					_character->ResetDashValues();
					if (_collisionSideBinary & COLLIDE_UP)
						_character->SetDashCount(_character->GetMaxDashCount());

				}
				else if (!_dashTimer)
				{
					_character->ResetDashValues();
					if (_collisionSideBinary & COLLIDE_UP)
						_character->SetDashCount(_character->GetMaxDashCount());
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

Vector2f MovementComponent::GetDirectionByPositions(Vector2f _destination)
{
	
		Vector2f _entityPos = owner->GetPosition();
		if (IsNearlyEqual(_entityPos, _destination)) return Vector2f(0.0f, 0.0f);

		
		Vector2f _direction = _destination - _entityPos;
		Normalize(_direction);
	
		return _direction;
}
