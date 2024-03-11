#include "Tile.h"
#include"TextureManager.h"
#include "Macro.h"



Tile::Tile(const EntityType _type, const Vector2f& _position, const Vector2f& _size, const string& _path, Grid* _owner)
	: Entity({ S_APPEND("Tile"), _type , _position , _size , _path })
{
	isTangible = true;

	sf::Vector2i _localPos (static_cast<int>(_position.x)% 1920 , static_cast<int>(_position.y) % (1080 - 24));
	index = { _localPos.y / static_cast<int>(_size.y) , _localPos.x / static_cast<int>(_size.x) };

	isMarkedByGetStackOfTypeArroundTile = false;
	owner = _owner;
}
