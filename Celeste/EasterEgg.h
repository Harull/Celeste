#pragma once
#include "Tile.h"
#include "AnimationComponent.h"
#include "OtherWindow.h"

class EasterEgg : public Tile
{
	OtherWindow* otherWindow;
	bool use;

public:
	EasterEgg(const Vector2f& _position, const Vector2f& _size, const string& _path = "Assets/FraiseCursed.png");

public:
	void GetHit(int _collisionSideBinary);
};

