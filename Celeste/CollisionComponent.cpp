#include "CollisionComponent.h"
#include "MapManager.h"
#include"Character.h"
#include"EntityManager.h"
CollisionComponent::CollisionComponent(Entity* _owner, function<void(int _collisionSide)> _callback) : Component(_owner)
{
	callback = _callback;
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
				if (!_tile) continue;

				sf::Shape* _shapeTile = _tile->GetShape();

				// Normalement pas possible
				if (_shapeTile == _currentShape)continue;

				if (_floatRectBb.intersects(_shapeTile->getGlobalBounds()))
				{
					_collisionSideBinary |= ComputeRelativePosition(_currentShape, _shapeTile, _collisionSideBinary);
					_entityTypeBinary |= _tile->GetType();
				}
			}
		}
	}
	return _entityTypeBinary;
}

void CollisionComponent::CheckCollisionCharacter(int& _collisionSideBinary)
{
	sf::Shape* _currentShape = owner->GetShape();
	sf::FloatRect _floatRectBb = _currentShape->getGlobalBounds();
	_collisionSideBinary = COLLIDE_NONE;


	Character* _character =dynamic_cast<Character*>(EntityManager::GetInstance().Get("Character"));
	Shape* _shape = _character->GetShape();

				if (_floatRectBb.intersects(_shape->getGlobalBounds()))
				{
					_collisionSideBinary |= ComputeRelativePosition(_currentShape, _shape, _collisionSideBinary);
					
				}
			
		
	
	return;
}



void CollisionComponent::Update()
{
	if (!callback)return;
	int _collisionSide;
	CheckCollisionCharacter(_collisionSide);
	callback(_collisionSide);
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
