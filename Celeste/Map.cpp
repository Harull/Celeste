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
	const int _maxValue = _value * _value;
	for (int _i = 0; _i < _maxValue; _i++) {
		for (int _j = 0; _j < _maxValue; _j++) {
			maps[_i][_j] = (new SmallMap(_value));
		}
	}
}

