#include "../include/FragileTile.h"
#include "../include/CollisionComponent.h"
#include "../include/TimerManager.h"
#include "../include/TextureManager.h"
#include "../include/Macro.h"
#include "../include/EntityManager.h"


#define PATH_FRAGILE_TILE "../../../../assets/FragileTile.png"

FragileTile::FragileTile(const EntityType _type, const Vector2f& _position, const Vector2f& _size, const string& _path, Grid* _owner):Tile(_type,_position,_size,_path, _owner)
{
	collisionReaction = [this](int _collisionSide, int _collisionSideBinary) {GetHit(_collisionSide, _collisionSideBinary); };
	index = 0;

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
		SetIsShake(true);
		for (auto _tile : _vector)
		{
			_tile->GetHit(_collisionSide, _collisionSideBinary, false);
			_tile->SetIsShake(true);
		}

	}

	new Timer("TimerDestroy" + id,
		[this]() {
			SetIsShake(false);
			TextureManager::GetInstance().Load(shape, "../../../../assets/FragileTile_erase.png");
			isTangible = false;
		new Timer("TimerRespawn" + id, [this]() {
		
			Reset();
			}, seconds(4));
	
		}, seconds(0.8f));

}

void FragileTile::Reset()
{
	isTangible = true;
	SetIsShake(false);
	index = 0;
	shape->setPosition(GetOriginalPosition());
	TextureManager::GetInstance().Load(shape, PATH_FRAGILE_TILE);
	if (Timer* _timerDestroy = TimerManager::GetInstance().GetApproximately("TimerDestroy" + id))
	{
		_timerDestroy->SetToRemove(true);
	}if (Timer* _timerDestroy = TimerManager::GetInstance().GetApproximately("TimerRespawn" + id))
	{
		_timerDestroy->SetToRemove(true);
	}


}

void FragileTile::Update()
{
	if (GetIsShake())
	{
		index++;
		if (index % 2 == 0) {
			shape->setPosition(GetOriginalPosition());
		}
		else
		{
			ShakeShape(GetShape());
		}
	}

	
}

