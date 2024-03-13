#pragma once

#include "Tile.h"
#include "Timer.h"

class FragileTile:public Tile
{
	int index;

public:
	FragileTile(const EntityType _type, const Vector2f& _position, const Vector2f& _size, const string& _path, Grid* _owner);
public:

	void GetHit(int _collisionSide, int _collisionSideBinary, const bool _hitAllAround = true);

	Shape* GetShape() { return shape; }

	virtual void Reset()override;

	virtual void Update()override;

};


