#include "FragileWallTile.h"
#include "CollisionComponent.h"
#include "TextureManager.h"
#include "Game.h"
#include "SoundManager.h"

FragileWallTile::FragileWallTile(const EntityType _type, const Vector2f& _position, const Vector2f& _size, const string& _path, Grid* _owner) : Tile(_type, _position, _size, _path, _owner)
{
	collisionReaction = [this](int _collisionSide, int _collisionSideBinary) {GetHit(_collisionSide, _collisionSideBinary); };
}

void FragileWallTile::GetHit(int _collisionSideBinary, int _collisionTypeBinary)
{
	if (isTangible == false)return;
	if (_collisionTypeBinary != ENTITY_CHARACTER)return;
	auto _vectorTest = GetStackOfTypeArround<FragileWallTile>();
	owner->ResetAllMarks();

	Character* _currentChar = Game::GetInstance().GetPlayer()->GetCharacter();
	if (_currentChar->GetIsDashing())
	{
		SoundManager::GetInstance().Play("wallbreak_ice.wav", 5.0f);
		_currentChar->Bonk(_collisionSideBinary);
		isTangible = false;
		TextureManager::GetInstance().Load(shape, "Assets/Vide.png");
	}

}

void FragileWallTile::Reset()
{
	isTangible = true;
	TextureManager::GetInstance().Load(shape, "Assets/Snow2.png");
}

