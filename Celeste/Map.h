#pragma once
#include "Grid.h"
#include "IManageable.h"
#include "SmallMap.h"
#include <vector>
using namespace std;

class Map : public IManageable<string>
{
	vector<vector<SmallMap*>> maps;
	Vector2f startPosition;

public:
	vector<vector<SmallMap*>>& GetMaps() { return maps; }

	vector<Drawable*> GetDrawables() {
		vector<Drawable*> _drawables;
		for (vector<SmallMap*> _smallMap : maps) {
			for (SmallMap* _sMap : _smallMap) {
				for (Drawable* _drawable : _sMap->GetGrid()->GetDrawablesMap()) {
					_drawables.push_back(_drawable);
				}
			}
		}
		return _drawables;
	}

	Vector2f GetStartPosition() { return startPosition; }
public:
	Map();

private:
	virtual void Register() override;

public:
	void Init(const int _value);

};