#include "MovingTile.h"
#include "Game.h"
#include "MovementComponent.h"


MovingTile::MovingTile(const EntityType _type, const Vector2f& _position, const Vector2f& _size, const string& _path):Tile(_type, _position, _size, _path)
{
	destination.push_back(_position);
	components.push_back(new MovementComponent(this,false,true));
	currentDestination = Vector2f();
	collisionReaction = [this](int _collisionSide, int _collisionSideBinary) {Move(_collisionSide, _collisionSideBinary); };
	indexDestination = 0;
	activated = false;
	
}

void MovingTile::CarryCharacter()
{
	Character* _character = Game::GetInstance().GetPlayer()->GetCharacter();
	MovementComponent* _thisMvCp = GetComponent<MovementComponent>();
	if (!_character || !(_character->GetShape()->getGlobalBounds().intersects(shape->getGlobalBounds()))|| !_thisMvCp->GetCanMove())
		return;
	if (MovementComponent* _chMvCp = Game::GetInstance().GetPlayer()->GetCharacter()->GetComponent<MovementComponent>())
	{
		
		_chMvCp->Move(_thisMvCp->GetDirection() * _thisMvCp->GetVelocity() / _chMvCp->GetVelocity());
	}
}

void MovingTile::Move(int _collisionSide, int _collisionSideBinary)
{
	if (_collisionSide != COLLIDE_UP)return;
	if (_collisionSideBinary != ENTITY_CHARACTER)return;
	MovementComponent* _move = GetComponent<MovementComponent>();
	
	if (activated)return;

	indexDestination = 1;
	activated = true;
	_move->SetCanMove(true);
	UpdateDirection();
}

void MovingTile::Update()
{
	CarryCharacter();
	Entity::Update();
	MovementComponent* _move = GetComponent<MovementComponent>();
	if(!_move->IsAtLocation(currentDestination))return;
	if (indexDestination == 0)
	{
		_move->SetCanMove(false);
		new Timer("Reload" + id, [this]() {
			activated = false;
			}, seconds(2.5), true, false);
		
		return;
		
	}
	else if (indexDestination >= destination.size()-1)
	{
		indexDestination = 0;
	}
	else
	{
		indexDestination++;
	}

	_move->SetCanMove(false);
	new Timer("Stop" + id, [this]() {
		MovementComponent* _move = GetComponent<MovementComponent>();
		_move->SetCanMove(true);
		}, seconds(2.5), true, false);
	UpdateDirection();
	
}
