#pragma once
#include"Tile.h"
class FallingTile:public Tile
{
	bool use;
	int index;
	bool isComplete;
	Vector2f startPosition;

public:
	FallingTile(const EntityType _type, const Vector2f& _position, const Vector2f& _size, const string& _path, Grid* _owner);

public:
	void MarkHasComplete()
	{
		components.clear();
		isComplete = true;
	}

public:
	void GetHit(int _collisionSide, int _collisionSideBinary, const bool _hitAllAround = true);
	void Update()override;
	virtual void Reset()override;
	void CarryCharacter();
};

