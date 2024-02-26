#pragma once
#include "Entity.h"



class Tile
{
	EntityType type;
	Shape* shape;
	Vector2f position;
	Vector2f size;
	string path;

public:
	Shape* GetShape()
	{
		return shape;
	}
	void SetEntity(EntityType _type)
	{
		type = _type;
	}
	EntityType GetType() const { return type; }

public:
	Tile();
	Tile(const Vector2f& _position, const Vector2f& _size, const string& _path, const EntityType& _type = ENTITY_NONE);
};