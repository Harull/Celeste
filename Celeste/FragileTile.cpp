#include "FragileTile.h"
#include"CollisionComponent.h"
#include"TimerManager.h"
#include "TextureManager.h"

#define PATH_FRAGILE_TILE "Assets/FragileTile.png"

FragileTile::FragileTile(const EntityType _type, const Vector2f& _position, const Vector2f& _size, const string& _path, Grid* _owner):Tile(_type,_position,_size,_path, _owner)
{
	collisionReaction = [this](int _collisionSide, int _collisionSideBinary) {GetHit(_collisionSide, _collisionSideBinary); };
}

void FragileTile::GetHit(int _collisionSide, int _collisionSideBinary)
{
	if (_collisionSide != COLLIDE_UP)return;
	if (_collisionSideBinary != ENTITY_CHARACTER)return;
	if (TimerManager::GetInstance().GetApproximately("TimerDestroy" + id ))return;
	if (TimerManager::GetInstance().GetApproximately("TimerRespawn" + id ))return;
	
	new Timer("TimerDestroy" + id,
		[this]() {
			
			TextureManager::GetInstance().Load(shape, "Assets/FragileTile_erase.png");
	isTangible = false;
		new Timer("TimerRespawn" + id, [this]() {
		
			isTangible = true;
			TextureManager::GetInstance().Load(shape, PATH_FRAGILE_TILE); 
			}, seconds(5));
	
		}, seconds(2));

}
