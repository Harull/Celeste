#include "MovingTile.h"

MovingTile::MovingTile(const EntityType _type, const Vector2f& _position, const Vector2f& _size, const string& _path):Tile(_type, _position, _size, _path)
{
	destination.push_back(_position);
	components.push_back(new MovementComponent(this,false));
	currentDestination = Vector2f();
	collisionReaction = [this](int _collisionSide, int _collisionSideBinary) {Move(_collisionSide, _collisionSideBinary); };
	indexDestination = 0;
}

void MovingTile::Move(int _collisionSide, int _collisionSideBinary)
{
	if (_collisionSide != COLLIDE_UP)return;
	if (_collisionSideBinary != ENTITY_CHARACTER)return;
	MovementComponent* _move = GetComponent<MovementComponent>();
	indexDestination = 1;
	
	if (_move->GetCanMove())return;
	

	_move->SetCanMove(true);
	UpdateDirection();


}

void MovingTile::Update()
{
	Entity::Update();
	MovementComponent* _move = GetComponent<MovementComponent>();
	if(!_move->IsAtLocation(currentDestination))return;
	
	if (indexDestination == 0)
	{
		_move->SetCanMove(false);
		
	}
	if (indexDestination >= destination.size()-1)
	{
		indexDestination = 0;
		UpdateDirection();
		return;
	}

	indexDestination++;
	UpdateDirection();

}
