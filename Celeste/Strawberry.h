#pragma once
#include "Tile.h"
#include "AnimationComponent.h"

class Strawberry : public Tile
{
	bool use;
public:
	Strawberry(const Vector2f& _position, const Vector2f& _size, const string& _path = "Assets/Fraise.png");

public:
	void GetHit(int _collisionSideBinary);
};

