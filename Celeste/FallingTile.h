#pragma once
#include"Tile.h"
class FallingTile:public Tile
{
	bool use;
	Vector2f startPosition;
public:
	FallingTile(const EntityType _type, const Vector2f& _position, const Vector2f& _size, const string& _path, Grid* _owner);

public:
	void GetHit(int _collisionSide, int _collisionSideBinary);
	void Update()override;
	virtual void Reset()override;
	void CarryCharacter();
};

