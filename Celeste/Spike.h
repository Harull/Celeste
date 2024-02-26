#pragma once
#include"Trap.h"


class Spike : public Trap
{
public:
	Spike( const Vector2f& _position, const Vector2f& _size, const string& _path, const EntityType& _type);

};

