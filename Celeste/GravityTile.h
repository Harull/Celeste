#pragma once
#include "Tile.h"
class GravityTile:public Tile
{

	bool use;

public:
	GravityTile(const EntityType _type, const Vector2f& _position, const Vector2f& _size, const string& _path, Grid* _owner);

public:
	void GetHit(int _collisionSide, int _collisionSideBinary);
	virtual void Reset()override;
};

