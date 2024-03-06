#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>
using namespace sf;
#include <string>
using namespace std;

class Tile : public Entity
{
	string name;

protected:
	bool isTangible;
public:
	bool GetIsTangible() const 
	{
		return isTangible;
	}
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
	Tile() = default;
	Tile(const EntityType _type, const Vector2f& _position, const Vector2f& _size, const string& _path);

};