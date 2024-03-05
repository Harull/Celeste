#include "FragileWallTile.h"
#include"CollisionComponent.h"
#include "TextureManager.h"
#include "Game.h"

FragileWallTile::FragileWallTile(const EntityType _type, const Vector2f& _position, const Vector2f& _size, const string& _path) :Tile(_type, _position, _size, _path)
{
	collisionReaction = [this](int _collisionSide, int _collisionSideBinary) {GetHit(_collisionSide, _collisionSideBinary); };
}

void FragileWallTile::GetHit(int _collisionSide, int _collisionSideBinary)
{
	if (_collisionSideBinary != ENTITY_CHARACTER)return;

	if (Game::GetInstance().GetPlayer()->GetCharacter()->GetIsDashing())
	{
		tangible = false;
		TextureManager::GetInstance().Load(shape, "Assets/Vide.png");
	}

}
