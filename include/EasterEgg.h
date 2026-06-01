#pragma once
#include "Tile.h"
#include "AnimationComponent.h"
#include "OtherWindow.h"

class EasterEgg : public Tile
{
	OtherWindow* otherWindow;
	bool isUsed;

public:
	EasterEgg(const Vector2f& _position, const Vector2f& _size, Grid* _owner, const string& _path = "../../../../assets/FraiseCursed.png");
	~EasterEgg();
public:
	void GetHit(int _collisionSideBinary);
};

