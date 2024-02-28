#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Tile.h"
#include "StreamManager.h"

using namespace std;
using namespace sf;

#define PATH_LEVEL "Save/Map"
#define PATH_VILLAGE_MAP "Save/village.txt"

class Grid
{
	Vector2i tilesCount;
	Vector2f tileSize;
	vector<vector<Tile*>> tiles;
	Vector2f spawnPosition;

public:

	vector<Tile*> GetTilesMap()
	{
		vector<Tile*> _newTiles;

		for (vector<Tile*> _tiles : tiles)
		{
			_newTiles.insert(_newTiles.end(), _tiles.begin(), _tiles.end());
		}

		return _newTiles;
	}

	vector<Drawable*> GetDrawablesMap()
	{
		vector<Drawable*> _drawables;

		for (vector<Tile*> _tiles : tiles)
		{
			for (Tile* _tile : _tiles)
			{
				if (!_tile)continue;
				_drawables.push_back(_tile->GetShape());
			}
		}
		return _drawables;
	}

	vector<Shape*> GetShapesMap() {
		vector<Shape*> _shapes;

		for (vector<Tile*> _tiles : tiles)
		{
			for (Tile* _tile : _tiles)
			{
				if (!_tile) continue;
				_shapes.push_back(_tile->GetShape());
			}

		}
		return _shapes;
	}
	
	Vector2f GetSpawnPosition()
	{
		return spawnPosition;
	}

	const Vector2f& GetTileSize()
	{
		return tileSize;
	}

public:
	Grid(const Vector2i _tilesCount);

public:
	void InitMap(const int _level, const int _value, Vector2f _startPos);
	void InitLevelSelection();
};