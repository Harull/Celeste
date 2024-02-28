#include "Trap.h"

Trap::Trap( const Vector2f& _position, const Vector2f& _size,const string& _path, const EntityType& _type ) :
	Tile(_type, _position, _size, _path)
{
}
