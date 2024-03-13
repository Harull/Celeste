#include "FallingTile.h"
#include "GravityComponent.h"
#include "MovementComponent.h"
#include "CollisionComponent.h"
#include "Character.h"
#include "Game.h"
#include "Camera.h"

FallingTile::FallingTile(const EntityType _type, const Vector2f& _position, const Vector2f& _size, const string& _path, Grid* _owner):
	Tile(_type, _position, _size, _path, _owner)
{
	use = false;
	isComplete = false;
	collisionReaction = [this](int _collisionSide, int _collisionSideBinary) {GetHit(_collisionSide, _collisionSideBinary); };
	startPosition = _position;

}

void FallingTile::GetHit(int _collisionSide, int _collisionSideBinary, const bool _hitAllAround)
{
	if (_collisionSideBinary == ENTITY_CHARACTER && !use)
	{
		components.push_back(new GravityComponent(this, 4.5f));
		components.push_back(new MovementComponent(this));
		components.push_back(new CollisionComponent(this));
		use = true;

		if (_hitAllAround)
		{
			auto _vector = this->GetStackOfTypeArround<FallingTile>();
			for (auto _tile : _vector)
			{
				_tile->GetHit(_collisionSide, _collisionSideBinary, false);
			}
		}
	}
	
	
}

void FallingTile::Update()
{
	if (isComplete)return;
	CarryCharacter();
	Entity::Update();

	sf::FloatRect _rect(Camera::GetInstance().getCenter() - Camera::GetInstance().getSize() / 2.0f, Camera::GetInstance().getSize());
	/*if (!_rect.intersects(shape->getGlobalBounds())) {
		components.clear();
		return;
	}*/

	if (CollisionComponent* _collision = GetComponent<CollisionComponent>())
	{
		CollisionInfos _info =_collision->CheckCollision();

		if ((_info.collisionSideBinary & COLLIDE_LEFT) && (_info.entityTypeBinary & ENTITY_TILE) && _info.entityTypeBinary ^ ENTITY_FALLING_TILE)
		{
			MarkHasComplete();

			auto _vector = this->GetStackOfTypeArround<FallingTile>();
			for (auto _tile : _vector)
			{
				_tile->MarkHasComplete();
			}
		}
	}
}
void FallingTile::CarryCharacter()
{
	Character* _character = Game::GetInstance().GetPlayer()->GetCharacter();
	MovementComponent* _thisMvCp = GetComponent<MovementComponent>();
	
	if (!_character || !(_character->GetShape()->getGlobalBounds().intersects(shape->getGlobalBounds())) ||_thisMvCp==nullptr)
		return;
	
	if (CollisionComponent* _collision = _character->GetComponent<CollisionComponent>())
	{
		CollisionInfos _currentInfos = _collision->CheckCollision(true);
		if (_currentInfos.collisionSideBinary & COLLIDE_UP ||
			_currentInfos.collisionSideBinary & COLLIDE_RIGHT ||
			_currentInfos.collisionSideBinary & COLLIDE_LEFT)
		{
			if (Game::GetInstance().GetPlayer()->GetCharacter()->GetIsClimbing())
			{
				if (MovementComponent* _chMvCp = Game::GetInstance().GetPlayer()->GetCharacter()->GetComponent<MovementComponent>())
				{
					sf::Vector2f _dirWithVelocity = _thisMvCp->GetDirection() * _thisMvCp->GetVelocity();
					std::cout << _dirWithVelocity.x << " | " << _dirWithVelocity.y << std::endl;
					_chMvCp->Move({ 0, 4.5f / 2.5f });
				}
			}
		}
	}


}

void FallingTile::Reset()
{
	shape->setPosition(startPosition);
	use = false;
	components.clear();
	isComplete = false;
}
