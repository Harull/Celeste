#include "GravityTile.h"
#include"CollisionComponent.h"
#include"Game.h"

GravityTile::GravityTile(const EntityType _type, const Vector2f& _position, const Vector2f& _size, const string& _path, Grid* _owner):Tile(_type, _position, _size, _path, _owner)
{
	use = false;
	collisionReaction = [this](int _collisionSide, int _collisionSideBinary) {GetHit(_collisionSide, _collisionSideBinary); };
}

void GravityTile::GetHit(int _collisionSide, int _collisionSideBinary)
{
	if (_collisionSide != COLLIDE_UP || _collisionSideBinary != ENTITY_CHARACTER||use)return;
	
	Game::GetInstance().ToggleSenseOfGravity();
	float _down = shape->getGlobalBounds().getSize().y/2;
	Vector2f _position =shape->getPosition();
	shape->setPosition(Vector2f(_position.x, _position.y + _down));
	shape->scale(1.f, 0.5f * Game::GetInstance().GetSenseOfGravity());
	use = true;
}

void GravityTile::Reset()
{
	if (shape->getGlobalBounds().getSize() == TILE_SIZE)return;
	
	float _down = shape->getGlobalBounds().getSize().y ;
	Vector2f _position = shape->getPosition();
	shape->setPosition(Vector2f(_position.x, _position.y - _down));
	shape->scale(1.f, 2.f);
	use = false;
}
