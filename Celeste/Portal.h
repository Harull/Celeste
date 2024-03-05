#pragma once
#include"Entity.h"
class Portal:public Entity
{
	Vector2f destination;
public:
	Portal(Vector2f _position,Vector2f _size);

public:
	void InitDestination();
	void Teleport();
};

