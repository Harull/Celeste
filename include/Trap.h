#pragma once
#include"Tile.h"

class Trap : public Tile
{
public:
	Trap( const Vector2f& _position, const Vector2f& _size, const string& _path,  const EntityType& _type, Grid* _owner);
};

