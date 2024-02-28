#include "Tile.h"
#include"TextureManager.h"
#include "Macro.h"

Tile::Tile(const EntityType _type, const Vector2f& _position, const Vector2f& _size, const string& _path) 
	: Entity({ S_APPEND("Tile"), _type , _position , _size , _path })
{

}
