#pragma once
#include "AnimationComponent.h"
#include "Tile.h"
#include "Character.h"

class GemDash : public Tile
{
	bool isUsed;

public:
	GemDash(const Vector2f& _position, const Vector2f& _size, Grid* _owner,const string& _path = "../../../../assets/Gem.png");

public:
	void GetHit(int _collisionSideBinary);
	virtual void Reset()override;
};

