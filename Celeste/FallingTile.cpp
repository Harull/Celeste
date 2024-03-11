#include "FallingTile.h"
#include"GravityComponent.h"
#include"MovementComponent.h"
#include"CollisionComponent.h"
#include"Character.h"
#include"Game.h"

FallingTile::FallingTile(const EntityType _type, const Vector2f& _position, const Vector2f& _size, const string& _path, Grid* _owner):Tile(_type, _position, _size, _path, _owner)
{
	use = false;
	collisionReaction = [this](int _collisionSide, int _collisionSideBinary) {GetHit(_collisionSide, _collisionSideBinary); };
	startPosition = _position;

}

void FallingTile::GetHit(int _collisionSide, int _collisionSideBinary)
{
	if (_collisionSideBinary == ENTITY_CHARACTER&&!use)
	{
		
		
		components.push_back(new GravityComponent(this, 4.5f));
		components.push_back(new MovementComponent(this));
		components.push_back(new CollisionComponent(this));
		use = true;
	}
	
}

void FallingTile::Update()
{
	CarryCharacter();
	Entity::Update();
	if (CollisionComponent* _collision = GetComponent<CollisionComponent>())
	{
		CollisionInfos _info =_collision->CheckCollision();
		if ((_info.collisionSideBinary & COLLIDE_LEFT) && (_info.entityTypeBinary  & ENTITY_TILE))
		{
			components.clear();
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
			if (MovementComponent* _chMvCp = Game::GetInstance().GetPlayer()->GetCharacter()->GetComponent<MovementComponent>())
			{
				sf::Vector2f _dirWithVelocity = _thisMvCp->GetDirection() * _thisMvCp->GetVelocity();
				//std::cout << "Move CarryCharacter" << std::endl;
				_chMvCp->Move({ _dirWithVelocity.x / _chMvCp->GetVelocity(), _dirWithVelocity.y });
			}
		}
	}


}

void FallingTile::Reset()
{
	shape->setPosition(startPosition);
	use = false;
}
