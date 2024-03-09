#include "SmallMap.h"


SmallMap::SmallMap(const int _level, const int _value, Vector2f _startPos)
{
	grid = new Grid(Vector2i(8, 8));
	level = _level;
	Init(_value, _startPos);
}

SmallMap::~SmallMap()
{
	delete grid;
	
}


void SmallMap::Init(const int _value, Vector2f _startPos)
{
	grid->InitMap(level, _value, _startPos);
}