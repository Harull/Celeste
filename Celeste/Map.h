#pragma once
#include "Grid.h"
#include "IManageable.h"
#include "SmallMap.h"
#include <vector>
using namespace std;

class Map : public IManageable<string>
{
	vector<vector<SmallMap*>> maps;

public:
	vector<vector<SmallMap*>>& GetMaps() { return maps; }

public:
	Map();

private:
	virtual void Register() override;

public:
	void Init(const int _value);

};