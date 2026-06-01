#pragma once
#include"Tile.h"
class CheckPoint:public Tile
{
	
public:
	CheckPoint(const EntityType _type, const Vector2f& _position, const Vector2f& _size, const string& _path, Grid* _owner);
public:
	void GetHit(int _collisionSide, int _collisionSideBinary);
};

