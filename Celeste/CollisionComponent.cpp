#include "CollisionComponent.h"
#include "MapManager.h"
#include"Character.h"
#include"EntityManager.h"
#include"FragileTile.h"


CollisionInfos CollisionComponent::CheckCollision()
{
	sf::Shape* _currentShape = owner->GetShape();
	sf::FloatRect _floatRectBb = _currentShape->getGlobalBounds();
	int _collisionSideBinary = COLLIDE_NONE;
	int _entityTypeBinary = ENTITY_NONE;
	float _minYOverlap = INFINITY, _minXOverlap = INFINITY;

	Map* _currentMap = MapManager::GetInstance().GetCurrent();
	if (!_currentMap) return { _entityTypeBinary, _collisionSideBinary };

	std::vector<std::vector<SmallMap*>> _allSmallMaps = _currentMap->GetMaps();
	for (auto _smallMapVect : _allSmallMaps)
	{
		for (SmallMap* _smallMap : _smallMapVect)
		{
			if (!_smallMap)continue;
			Grid* _currentGrid = _smallMap->GetGrid();
			std::vector<Tile*> _tiles = _currentGrid->GetTilesMap();
			for (Tile* _tile : _tiles)
			{
				if (!_tile) continue;
				if (!_tile->GetTangible())continue;

				sf::Shape* _shapeTile = _tile->GetShape();

				// Normalement pas possible
				if (_shapeTile == _currentShape)continue;

				const sf::FloatRect& _tileGbb = _shapeTile->getGlobalBounds();
				if (_floatRectBb.intersects(sf::FloatRect({ _tileGbb.left + 1, _tileGbb.top}, { _tileGbb.width - 2, _tileGbb.height})))
				{
					CollisionSide _currentSide = ComputeRelativePosition(_currentShape, _shapeTile, _collisionSideBinary);
					_collisionSideBinary |= _currentSide;
					_entityTypeBinary |= _tile->GetType();

					if (function<void(int _collisionSide, int _collisionSideBinary)>_collisionReaction = _tile->GetCollisionReaction())
						_collisionReaction(_collisionSideBinary, owner->GetType());

					if (_currentSide & COLLIDE_UP)
					{
						float _yCurrentOverlap = ComputeYOverlap(_currentShape, _shapeTile);
						_minYOverlap = _minYOverlap > _yCurrentOverlap ? _yCurrentOverlap : _minYOverlap;
					}
					else
					{
						float _xCurrentOverlap = ComputeXOverlap(_currentShape, _shapeTile);
						_minXOverlap = _minXOverlap > _xCurrentOverlap ? _xCurrentOverlap : _minXOverlap;
					}
				}
			}
		}
	}
	return { _entityTypeBinary, _collisionSideBinary, _minXOverlap, _minYOverlap};
}


void CollisionComponent::Update()
{

}

CollisionComponent::CollisionComponent(Entity* _owner):Component(_owner)
{

}

CollisionSide CollisionComponent::ComputeRelativePosition(const sf::Shape* _entityShape, const sf::Shape* _tileShape,
	const int initialCollisionSideBinary)
{
	const float _marginOfError = 50.f;

	sf::FloatRect _entityGlobalBounds = _entityShape->getGlobalBounds();
	const sf::FloatRect& _tileGlobalBounds = _tileShape->getGlobalBounds();
	
	float _overlapLeft = _tileGlobalBounds.left + _tileGlobalBounds.width - _entityGlobalBounds.left;
	_overlapLeft += _marginOfError;
	float _overlapRight = _entityGlobalBounds.left + _entityGlobalBounds.width - _tileGlobalBounds.left;
	_overlapRight += _marginOfError;
	float _overlapTop = _tileGlobalBounds.top + _tileGlobalBounds.height - _entityGlobalBounds.top;
	float _overlapBottom = _entityGlobalBounds.top + _entityGlobalBounds.height - _tileGlobalBounds.top;

	float _overlaps[] = { _overlapLeft, _overlapRight, _overlapTop, _overlapBottom };
	CollisionSide _sides[] = { CollisionSide::COLLIDE_LEFT, CollisionSide::COLLIDE_RIGHT, CollisionSide::COLLIDE_UP, CollisionSide::COLLIDE_DOWN };
	float _maxOverlap = _overlaps[0];
	CollisionSide _maxSide = _sides[0]; 

	for (int i = 1; i < 4; ++i) {
		if (_overlaps[i] > _maxOverlap) {
			_maxOverlap = _overlaps[i];
			_maxSide = _sides[i];
		}
	}
	return _maxSide;


	//TEST 2

	//CollisionSide _sideCollided = COLLIDE_NONE;
	//// Vérification des collisions avec le mur/sol

	//if (_entityGlobalBounds.intersects(_tileGlobalBounds)) {
	//	// Collision détectée, ajuster la position du personnage en fonction de la direction de la collision

	//	// Collision par la droite
	//	if (_entityGlobalBounds.left < _tileGlobalBounds.left && _entityGlobalBounds.left + _entityGlobalBounds.width > _tileGlobalBounds.left) {
	//		_entityGlobalBounds = sf::FloatRect({ _tileGlobalBounds.left + _tileGlobalBounds.width,_entityShape->getPosition().y }, _entityGlobalBounds.getSize());
	//		_sideCollided = COLLIDE_RIGHT;
	//	}
	//	// Collision par la gauche
	//	else if (_entityGlobalBounds.left > _tileGlobalBounds.left && _entityGlobalBounds.left < _tileGlobalBounds.left + _tileGlobalBounds.width) {
	//		_entityGlobalBounds = sf::FloatRect({ _tileGlobalBounds.left + _tileGlobalBounds.width, _entityShape->getPosition().y }, _entityGlobalBounds.getSize());
	//		_sideCollided = COLLIDE_LEFT;
	//	}
	//	// Collision par le bas
	//	if (_entityGlobalBounds.top < _tileGlobalBounds.top && _entityGlobalBounds.top + _entityGlobalBounds.height > _tileGlobalBounds.top) {
	//		_sideCollided = COLLIDE_DOWN;
	//		_entityGlobalBounds = sf::FloatRect({ _entityShape->getPosition().x, _tileGlobalBounds.top - _entityGlobalBounds.height }, _entityGlobalBounds.getSize());
	//	}
	//	// Collision par le haut
	//	else if (_entityGlobalBounds.top > _tileGlobalBounds.top && _entityGlobalBounds.top < _tileGlobalBounds.top + _tileGlobalBounds.height) {
	//		_sideCollided = COLLIDE_UP;
	//		_entityGlobalBounds = sf::FloatRect({ _entityShape->getPosition().x, _tileGlobalBounds.top + _tileGlobalBounds.height }, _entityGlobalBounds.getSize());
	//	}
	//}

	//return _sideCollided;
}


float CollisionComponent::ComputeYOverlap(const sf::Shape* _entityShape, const sf::Shape* _tileShape)
{
	const sf::FloatRect& _entityGlobalBounds = _entityShape->getGlobalBounds();
	const sf::FloatRect& _tileGlobalBounds = _tileShape->getGlobalBounds();

	CollisionSide _side = _entityGlobalBounds.top < _tileGlobalBounds.top ? COLLIDE_DOWN : COLLIDE_UP;

	if (_side & COLLIDE_DOWN)
		return _entityGlobalBounds.top + _entityGlobalBounds.height - _tileGlobalBounds.top;

	return _tileGlobalBounds.top + _tileGlobalBounds.height - _entityGlobalBounds.top;
}

float CollisionComponent::ComputeXOverlap(const sf::Shape* _entityShape, const sf::Shape* _tileShape)
{
	const sf::FloatRect& _entityGlobalBounds = _entityShape->getGlobalBounds();
	const sf::FloatRect& _tileGlobalBounds = _tileShape->getGlobalBounds();

	CollisionSide _side = _entityGlobalBounds.left < _tileGlobalBounds.left ? COLLIDE_LEFT : COLLIDE_RIGHT;

	if (_side & COLLIDE_LEFT)
		return  _entityGlobalBounds.left + _entityGlobalBounds.width - _tileGlobalBounds.left;

	return _tileGlobalBounds.left + _tileGlobalBounds.width - _entityGlobalBounds.left;
}

