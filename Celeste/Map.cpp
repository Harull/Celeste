#include "Map.h"
#include "Macro.h"
#include "MapManager.h"

Map::Map() : IManageable(S_APPEND("Map"))
{
}

void Map::Register()
{
	MapManager::GetInstance().Add(id, this);
}

void Map::Init(const int _value)
{

	const string _pathSmallMap = "Maps/Level" + to_string(_value) + "/Level" + to_string(_value) + ".txt";
	vector<vector<int>> _gridForLoad;
	StreamManager::GetInstance().LoadMapLevel(_gridForLoad, _pathSmallMap);

	int _i = 0;
	int _j = 0;
	vector<SmallMap*> _tempMaps;
	for (vector<int> _vMap : _gridForLoad) {
		for (int _sMap : _vMap) {
			_tempMaps.push_back(new SmallMap(_value, _sMap));
		}
		maps.push_back(_tempMaps);
	}

}

