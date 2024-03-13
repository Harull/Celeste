#include "FragileTile.h"
#include"CollisionComponent.h"
#include"TimerManager.h"
#include "TextureManager.h"
#include "Macro.h"

#define PATH_FRAGILE_TILE "Assets/FragileTile.png"

FragileTile::FragileTile(const EntityType _type, const Vector2f& _position, const Vector2f& _size, const string& _path, Grid* _owner):Tile(_type,_position,_size,_path, _owner)
{
	collisionReaction = [this](int _collisionSide, int _collisionSideBinary) {GetHit(_collisionSide, _collisionSideBinary); };
}

void FragileTile::GetHit(int _collisionSide, int _collisionSideBinary, const bool _hitAllAround)
{
	if (_collisionSide != COLLIDE_UP)return;
	if (_collisionSideBinary != ENTITY_CHARACTER)return;
	if (TimerManager::GetInstance().GetApproximately("TimerDestroy" + id ))return;
	if (TimerManager::GetInstance().GetApproximately("TimerRespawn" + id ))return;

	if (_hitAllAround)
	{
		auto _vector = this->GetStackOfTypeArround<FragileTile>();
		for (auto _tile : _vector)
		{
			_tile->GetHit(_collisionSide, _collisionSideBinary, false);
		}
		_vector.push_back(this);
		//ShakeBlocks(_vector);
	}

	new Timer("TimerDestroy" + id,
		[this]() {
			TextureManager::GetInstance().Load(shape, "Assets/FragileTile_erase.png");
			isTangible = false;
		new Timer("TimerRespawn" + id, [this]() {
		
			isTangible = true;
			TextureManager::GetInstance().Load(shape, PATH_FRAGILE_TILE); 
			}, seconds(4));
	
		}, seconds(0.8f));

}

void FragileTile::Reset()
{
	isTangible = true;
	TextureManager::GetInstance().Load(shape, PATH_FRAGILE_TILE);
	if (Timer* _timerDestroy = TimerManager::GetInstance().GetApproximately("TimerDestroy" + id))
	{
		_timerDestroy->SetToRemove(true);
	}if (Timer* _timerDestroy = TimerManager::GetInstance().GetApproximately("TimerRespawn" + id))
	{
		_timerDestroy->SetToRemove(true);
	}
}

