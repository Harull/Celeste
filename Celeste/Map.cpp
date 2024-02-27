#include "Map.h"
#include "Macro.h"
#include "MapManager.h"
#include "TextureManager.h"

Map::Map() : IManageable(S_APPEND("Map"))
{
	Vector2u _windowSize = Game::GetInstance().GetWindowSize();
	const float _startPosX = 0.0f;
	const float _startPosY = -48.0f;
	startPosition = Vector2f(_startPosX, _startPosY);
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
		maps.push_back(_tempMaps);
		_i = 0;
		_startPosition.x = startPosition.x;
		_startPosition.y += _tempMaps[_i]->GetGrid()->GetTileSize().y * 22;
		_tempMaps.clear();
	}

}

