#pragma once
#include"Entity.h"

class Trap : public Entity
{
public:
	Trap(const string& _name, const Vector2f& _position, const Vector2f& _size, const string& _path);
};

