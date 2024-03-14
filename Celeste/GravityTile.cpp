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
}
