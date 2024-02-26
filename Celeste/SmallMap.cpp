#include "SmallMap.h"


SmallMap::SmallMap(const int _level, const int _value)
{
	grid = new Grid(Vector2i(8, 8));
	level = _level;
	Init(_value);
}


void SmallMap::Init(const int _value)
{
	grid->InitMap(level, _value);
}