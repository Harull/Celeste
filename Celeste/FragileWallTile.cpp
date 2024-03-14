#include "FragileWallTile.h"
#include "CollisionComponent.h"
#include "TextureManager.h"
#include "Game.h"
#include "SoundManager.h"

FragileWallTile::FragileWallTile(const EntityType _type, const Vector2f& _position, const Vector2f& _size, const string& _path, Grid* _owner) : Tile(_type, _position, _size, _path, _owner)
{
	collisionReaction = [this](int _collisionSide, int _collisionSideBinary) {GetHit(_collisionSide, _collisionSideBinary); };
}

void FragileWallTile::GetHit(int _collisionSideBinary, int _collisionTypeBinary, const bool _hitAllAround)
{
	if (isTangible == false)return;
	if (_collisionTypeBinary != ENTITY_CHARACTER)return;
	owner->ResetAllMarks();

	if (_hitAllAround)
	{
		auto _vector = this->GetStackOfTypeArround<FragileWallTile>();
		for (auto _tile : _vector)
		{
			_tile->GetHit(_collisionSideBinary, _collisionTypeBinary, false);
		}
	}

	Character* _currentChar = Game::GetInstance().GetPlayer()->GetCharacter();
	if (_currentChar->GetIsDashing())
	{
		SoundManager::GetInstance().Play("wallbreak_ice.wav");
		_currentChar->Bonk(_collisionSideBinary);
		isTangible = false;
		TextureManager::GetInstance().Load(shape, "Assets/Vide.png");
	}

}



