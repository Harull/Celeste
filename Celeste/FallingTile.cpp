#include "FallingTile.h"
#include"GravityComponent.h"
#include"MovementComponent.h"
#include"CollisionComponent.h"
FallingTile::FallingTile(const EntityType _type, const Vector2f& _position, const Vector2f& _size, const string& _path):Tile(_type, _position, _size, _path)
{
	use = false;
	collisionReaction = [this](int _collisionSide, int _collisionSideBinary) {GetHit(_collisionSide, _collisionSideBinary); };

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
