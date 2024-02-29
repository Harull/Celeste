#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include <vector>
#include <functional>
#include "Tile.h"
#include "Component.h"
#include<functional>

enum CollisionSide
{
	COLLIDE_NONE = 0, COLLIDE_LEFT = 1 , COLLIDE_RIGHT = 2, COLLIDE_UP = 4, COLLIDE_DOWN = 8
};

class CollisionComponent : public Component
{
	function<void(int _collisionSide, int _collisionSideBinary)> callback;
public:
	CollisionComponent(Entity* _owner, function<void(int _collisionSide, int _collisionSideBinary)> _callback= function<void(int _collisionSide, int _collisionSideBinary)>());
private:
	CollisionSide ComputeRelativePosition(const sf::Shape* _entityShape, const sf::Shape* _tileShape,
		const int initialCollisionSideBinary);
public:
	int CheckCollision(int& _collisionSideBinary);
	void CheckCollisionCharacter(int& _collisionSideBinary);
	virtual void Update()override;


};

