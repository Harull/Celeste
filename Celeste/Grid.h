#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "StreamManager.h"

using namespace std;
using namespace sf;

#define PATH_LEVEL "Save/Map"
#define PATH_VILLAGE_MAP "Save/village.txt"
#define TILE_SIZE Vector2f(50.f,50.f)

class Tile;

class Grid
{
	Vector2i tilesCount;
	Vector2f tileSize;
	vector<vector<Tile*>> tiles;
	vector<vector<char>> gridForLoad;
	Vector2f spawnPosition;
	vector<Vector2f> tilePositionsEmpty;

public:

	vector<Tile*> GetTilesMap();

	vector<vector<Tile*>> GetTiles() const
	{
		return tiles;
	}

	vector<Drawable*> GetDrawablesMap();

	vector<Shape*> GetShapesMap();
	
	Vector2f GetSpawnPosition()
	{
		return spawnPosition;
	}

	const Vector2f& GetTileSize()
	{
		return tileSize;
	}

	vector<Vector2f> GetPositionsTileEmpty() {
		return tilePositionsEmpty;
	}

public:
	Grid(const Vector2i _tilesCount);
	void ChangeTexture();
	void FinalMap(const int _i, const  int _j, const char _char);
	void RotateSpike(Tile* _spikeTile, const std::pair<int, int> _index, const sf::Vector2f& _spikePositionOffset);
	void RotateAllSpikes(const sf::Vector2f& _spikePositionOffset);
	bool IsIndexValid(const std::pair<int, int> _index);

public:
	void InitMap(const int _level, const int _value, Vector2f _startPos);
	void ResetAllMarks();

	

};