#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include <vector>
#include <functional>
#include "Tile.h"
#include "Component.h"
#include <iostream>

enum CollisionSide
{
	COLLIDE_NONE = 0, COLLIDE_LEFT = 1 , COLLIDE_RIGHT = 2, COLLIDE_UP = 4, COLLIDE_DOWN = 8
};

struct CollisionInfos
{
	int entityTypeBinary;
	int collisionSideBinary;
	float smallestXOverlap;
	float smallestYOverlap;
};

class CollisionComponent : public Component
{
	function<void(int _collisionSide, int _collisionSideBinary)> callback;
public:
	CollisionComponent(Entity* _owner, function<void(int _collisionSide, int _collisionSideBinary)> _callback= function<void(int _collisionSide, int _collisionSideBinary)>());
private:
	CollisionSide ComputeRelativePosition(const sf::Shape* _entityShape, const sf::Shape* _tileShape,
		const int initialCollisionSideBinary);
	float ComputeYOverlap(const sf::Shape* _entityShape, const sf::Shape* _tileShape);
	float ComputeXOverlap(const sf::Shape* _entityShape, const sf::Shape* _tileShape);

public:
	/// <summary>
	/// Fonction donnant les infos sur les entités rentrées en collision avec mes objets
	/// </summary>
	/// <returns>Retourne:
	/// [- les types avec lequel il a collide]
	/// [- la façon dont il a collide les objets qui ont une collision] [autre chose]</returns>
	CollisionInfos CheckCollision();

	virtual void Update()override;


};

