#include "Map.h"
#include "Macro.h"
#include "MapManager.h"
#include "TextureManager.h"
#include "Game.h"
#include"Grid.h"

Map::Map() : IManageable(S_APPEND("Map"))
{
	Vector2u _windowSize = Game::GetInstance().GetWindowSize();
	const float _startPosX = 0.0f;
	const float _startPosY = -48.0f;
	startPosition = Vector2f(_startPosX, _startPosY);
	Register();
}





void Map::Register()
{
	MapManager::GetInstance().Add(id, this);
}

void Map::Init(const int _value)
{
	const string _path = "Maps/Level" + to_string(_value) + "/Level" + to_string(_value);
	const string _pathSmallMap = _path + ".txt";
	vector<vector<int>> _gridForLoad;
	StreamManager::GetInstance().LoadMapLevel(_gridForLoad, _pathSmallMap);

	int _i = 0;
	vector<SmallMap*> _tempMaps;
	Vector2f _startPosition = startPosition;
	for (vector<int> _vMap : _gridForLoad) {
		for (int _sMap : _vMap) {
			_tempMaps.push_back(new SmallMap(_value, _sMap, _startPosition));
			_startPosition.x += _tempMaps[_i]->GetGrid()->GetTileSize().x * 40;
			_i++;
		}
		_i = 0;
		maps.push_back(_tempMaps);
		_startPosition.x = startPosition.x;
		_startPosition.y += _tempMaps[_i]->GetGrid()->GetTileSize().y * 22;
		_tempMaps.clear();
	}
	Vector2f _spawn;
	float _distance = TILE_SIZE.x * 5;
	for (vector<SmallMap*> _maps : maps)
	{
		for (SmallMap* _map:_maps)
		{
			for (vector<Tile*> _tiles : _map->GetGrid()->GetTiles())
			{
				for (Tile* _tile : _tiles)
				{
					if (!_tile)continue;
					
					if (_tile->GetType()==ENTITY_CHECKPOINT)
					{
						Vector2f _position = _tile->GetPosition();
						if (_spawn== Vector2f() || (_position.x < _distance&&_position.y<_spawn.y))
						{
							_spawn = _position;
							
						}
						
					}
				}
			}
		}
	}
	Game::GetInstance().GetPlayer()->GetCharacter()->GetShape()->setPosition(_spawn);
}

