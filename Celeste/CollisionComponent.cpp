#include "CollisionComponent.h"
#include "MapManager.h"

CollisionComponent::CollisionComponent(Entity* _owner) : Component(_owner)
{
}

int CollisionComponent::CheckCollision(int& _collisionSideBinary)
{
	sf::Shape* _currentShape = owner->GetShape();
	sf::FloatRect _floatRectBb = _currentShape->getGlobalBounds();
	_collisionSideBinary = COLLIDE_NONE;
	int _entityTypeBinary = ENTITY_NONE;


	Map* _currentMap = MapManager::GetInstance().GetCurrent();
	if (!_currentMap) return _entityTypeBinary;

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
				sf::Shape* _shapeTile = _tile->GetShape();

				// Normalement pas possible
				if (_shapeTile == _currentShape)continue;

				if (_floatRectBb.intersects(_shapeTile->getGlobalBounds()))
				{
					_collisionSideBinary = ComputeRelativePosition(_currentShape, _shapeTile, _collisionSideBinary);

					return _tile->GetType();
				}
			}
		}
	}
	return _entityTypeBinary;
}

int CollisionComponent::ComputeRelativePosition(const sf::Shape* _entityShape, const sf::Shape* _tileShape,
	const int initialCollisionSideBinary)
{
	int _resultPosition = initialCollisionSideBinary;
	const float marginOfError = 1.0f;

	const sf::FloatRect& _entityGlobalBounds = _entityShape->getGlobalBounds();
	const sf::FloatRect& _tileGlobalBounds = _tileShape->getGlobalBounds();

	if (_entityGlobalBounds.top + _entityGlobalBounds.height >= _tileGlobalBounds.top - marginOfError)
		_resultPosition |= COLLIDE_UP;
	if (_entityGlobalBounds.top <= _tileGlobalBounds.top + _entityGlobalBounds.height + marginOfError)
		_resultPosition |= COLLIDE_DOWN;
	if (_entityGlobalBounds.left + _entityGlobalBounds.width <= _tileGlobalBounds.left + marginOfError)
		_resultPosition |= COLLIDE_LEFT;
	if (_entityGlobalBounds.left >= _tileGlobalBounds.left + _tileGlobalBounds.width - marginOfError)
		_resultPosition |= COLLIDE_RIGHT;

	return _resultPosition;
}
