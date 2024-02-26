#include "SmallMap.h"


SmallMap::SmallMap(const int _value)
{
	grid = new Grid(Vector2i(8, 8));
	Init(_value);
}


void SmallMap::Init(const int _value)
{
	grid->InitMap(_value);
}