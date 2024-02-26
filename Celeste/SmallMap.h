#pragma once
#include "Grid.h"

class SmallMap
{
	Grid* grid;

public:
	Grid* GetGrid()
	{
		return grid;
	}

private:
	void Init(const int _value);

public:
	SmallMap(const int _value);
};

