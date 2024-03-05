#pragma once
#include "Tile.h"
class FragileWallTile :public Tile
{

public:
	FragileWallTile(const EntityType _type, const Vector2f& _position, const Vector2f& _size, const string& _path);
public:

	void GetHit(int _collisionSide, int _collisionSideBinary);
};


