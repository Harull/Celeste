#pragma once
#include "AnimationComponent.h"
#include "Tile.h"
#include "Character.h"

class GemDash : public Tile
{
	bool use;

public:
	GemDash(const Vector2f& _position, const Vector2f& _size, const string& _path = "Assets/Gem.png");

public:
	void GetHit(int _collisionSideBinary);
};

