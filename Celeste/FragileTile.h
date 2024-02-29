#pragma once
#include "Tile.h"
#include"Timer.h"
class FragileTile:public Tile
{
	bool destroying;
public:
	FragileTile(const EntityType _type, const Vector2f& _position, const Vector2f& _size, const string& _path);
public:

	void GetHit(int _collisionSide, int _collisionSideBinary);
};

