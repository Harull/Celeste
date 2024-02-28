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
				vector<Drawable*> _drawableVect = _sMap->GetGrid()->GetDrawablesMap();
				for (Drawable* _drawable : _drawableVect) {
					_drawables.push_back(_drawable);
				}
			}
		}
		return _drawables;
	}

	vector<Shape*> GetShapesMap() {
		vector<Shape*> _shapeVectToReturn;

		for (vector<SmallMap*> _smallMap : maps) {
			for (SmallMap* _sMap : _smallMap) {
				vector<Shape*> _shapeVect = _sMap->GetGrid()->GetShapesMap();
				for (Shape* _shape : _shapeVect) {
					_shapeVectToReturn.push_back(_shape);
				}
			}
		}
		return _shapeVectToReturn;
	}


	Vector2f GetStartPosition() { return startPosition; }
public:
	Map();

private:
	virtual void Register() override;

public:
	void Init(const int _value);

};