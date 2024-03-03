#pragma once
#include"Trap.h"
#include "Character.h"

class Spike : public Trap
{
	Character* character;

public:
	Spike( const Vector2f& _position, const Vector2f& _size, const string& _path, const EntityType& _type);

public:
	void GetHit(int _collisionSide, int _collisionSideBinary);


};

