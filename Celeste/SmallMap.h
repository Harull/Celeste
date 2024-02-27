#pragma once
#include "Grid.h"

class SmallMap
{
	Grid* grid;
	int level;

public:
	Grid* GetGrid()
	{
		return grid;
	}

private:
	void Init(const int _value, Vector2f _startPos);

public:
	SmallMap(const int _level, const int _value, Vector2f _startPos);
};

