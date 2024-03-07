#include "FragileWallTile.h"
#include "CollisionComponent.h"
#include "TextureManager.h"
#include "Game.h"

FragileWallTile::FragileWallTile(const EntityType _type, const Vector2f& _position, const Vector2f& _size, const string& _path) :Tile(_type, _position, _size, _path)
{
	collisionReaction = [this](int _collisionSide, int _collisionSideBinary) {GetHit(_collisionSide, _collisionSideBinary); };
}

void FragileWallTile::GetHit(int _collisionSideBinary, int _collisionTypeBinary)
{
	if (_collisionTypeBinary != ENTITY_CHARACTER)return;
	Character* _currentChar = Game::GetInstance().GetPlayer()->GetCharacter();
	if (_currentChar->GetIsDashing())
	{
		_currentChar->Bonk(_collisionSideBinary);
		isTangible = false;
		TextureManager::GetInstance().Load(shape, "Assets/Vide.png");
	}

}
