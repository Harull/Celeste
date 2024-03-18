#pragma once
#include"Tile.h"
class FallingTile:public Tile
{
	bool use;
	bool isComplete;
	Vector2f startPosition;
	bool hasShaken;

public:
	FallingTile(const EntityType _type, const Vector2f& _position, const Vector2f& _size, const string& _path, Grid* _owner);

public:
	void MarkHasComplete()
	{
		components.clear();
		isComplete = true;
	}
	void SetHasShaken(const bool _status)
	{
		hasShaken = _status;
	}

public:
	void GetHit(int _collisionSide, int _collisionSideBinary, const bool _hitAllAround = true);
	void Update()override;
	virtual void Reset()override;
	void CarryCharacter();
	void ShakeAllFallingTilesAround();
};

