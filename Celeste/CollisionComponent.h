#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include <vector>
#include <functional>
#include "Tile.h"

enum CollisionSide
{
	COLLIDE_NONE = 0, COLLIDE_LEFT = 1 , COLLIDE_RIGHT = 2, COLLIDE_UP = 4, COLLIDE_DOWN = 8
};

class CollisionComponent
{
public:
	int CheckCollision(Entity* _entity, int& _collisionSideBinary);

private:
	int ComputeRelativePosition(const sf::Shape* _entityShape, const sf::Shape* _tileShape,
		const int initialCollisionSideBinary);
};

