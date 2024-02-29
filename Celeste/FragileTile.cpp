#include "FragileTile.h"
#include"CollisionComponent.h"
#include"TimerManager.h"
#include "TextureManager.h"
#define PATH_FRAGILE_TILE "Assets/Snow1.png"
FragileTile::FragileTile(const EntityType _type, const Vector2f& _position, const Vector2f& _size, const string& _path):Tile(_type,_position,_size,_path)
{
	collisionReaction = [this](int _collisionSide, int _collisionSideBinary) {GetHit(_collisionSide, _collisionSideBinary); };
}

void FragileTile::GetHit(int _collisionSide, int _collisionSideBinary)
{
 	Color _color=shape->getFillColor();
	if (_collisionSide != COLLIDE_UP)return;
	if (_collisionSideBinary != ENTITY_CHARACTER)return;
	if (TimerManager::GetInstance().Get("TimerDestroy" + id ))return;
	if (TimerManager::GetInstance().Get("TimerRespawn" + id ))return;
	
	new Timer("TimerDestroy" + id,
		[this]() {
			TextureManager::GetInstance().Load(shape, " ");
	tangible = false;
		new Timer("TimerRespawn" + id, [this]() {
			
			tangible = true;
			TextureManager::GetInstance().Load(shape, PATH_FRAGILE_TILE); 
			}, seconds(5));
	
		}, seconds(2));



	
}
