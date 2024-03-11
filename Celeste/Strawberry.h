#pragma once
#include "Tile.h"
#include "AnimationComponent.h"

class Strawberry : public Tile
{
	bool isUsed;
public:
	Strawberry(const Vector2f& _position, const Vector2f& _size, Grid* _owner, const string& _path = "Assets/Fraise.png");

public:
	void GetHit(int _collisionSideBinary);
};

