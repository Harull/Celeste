#include "Grid.h"

Grid::Grid(const Vector2i _tilesCount)
{
	tilesCount = _tilesCount;
	tileSize = Vector2f(50.0f, 50.0f);
	tiles = vector<vector<Tile*>>();
	spawnPosition = Vector2f();
}


void Grid::InitMap(const int _value)
{
	tileSize = Vector2f(150.0f, 150.0f);
	vector<vector<string>> _gridForLoad;
	StreamManager::GetInstance().LoadMap(_gridForLoad, "Map" + to_string(_value) + ".txt");
	//
	Vector2u _windowSize = Vector2u(1200, 800);

	const float _startPosX = _windowSize.x * 0.35f;
	const float _startPosY = _windowSize.y * 0.1f;

	string _path;
	vector<Tile*> _tiles;
	int _indexRow = -1, _indexColumn = -1;
	EntityType _type;

	for (const vector<string>& _lines : _gridForLoad) {
		_indexColumn++;
		for (int _indexRow = 0; _indexRow < static_cast<int>(_lines.front().size()); _indexRow++)
		{
			char _char = _lines.front()[_indexRow];
			const float _posX = static_cast<float>(_indexRow * tileSize.x + _startPosX);
			const float _posY = static_cast<float>(_indexColumn * tileSize.y + _startPosY);
			if (_char == ' ')
			{
				_path = " ";
				_type = ENTITY_TILE;
			}
		}
		
		tiles.push_back(_tiles);
		_tiles.clear();
	}

}

void Grid::InitLevelSelection()
{
}
