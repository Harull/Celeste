#include "Grid.h"
#include "Game.h"

Grid::Grid(const Vector2i _tilesCount)
{
	tilesCount = _tilesCount;
	tileSize = Vector2f(50.0f, 50.0f);
	tiles = vector<vector<Tile*>>();
	spawnPosition = Vector2f();
}


void Grid::InitMap(const int _level, const int _value)
{
	tileSize = Vector2f(150.0f, 150.0f);
	vector<vector<char>> _gridForLoad;
	const string _pathMap = "Maps/Level"+ to_string(_level) + "/Map" + to_string(_value) + ".txt";
	StreamManager::GetInstance().LoadSmallMap(_gridForLoad, _pathMap);
	//
	Vector2u _windowSize = Game::GetInstance().GetWindowSize();

	const float _startPosX = _windowSize.x * 0.35f;
	const float _startPosY = _windowSize.y * 0.1f;

	string _path;
	vector<Tile*> _tiles;
	vector<string> _test;
	int _indexRow = -1, _indexColumn = -1;
	EntityType _type;

	for (const vector<char>& _vChar : _gridForLoad) {
		_indexColumn++;
		for (const char& _char : _vChar) {

			const float _posX = static_cast<float>(_indexRow * tileSize.x + _startPosX);
			const float _posY = static_cast<float>(_indexColumn * tileSize.y + _startPosY);
			if (_char == ' ')
			{
				_path = " ";
				_type = ENTITY_TILE;
			}

			Tile* _tile = new Tile(Vector2f(_posX, _posY), tileSize, _path, _type);
			_tiles.push_back(_tile);
			_indexRow++;

		}
		_indexRow = 0;
		tiles.push_back(_tiles);
		_tiles.clear();
	}

}

void Grid::InitLevelSelection()
{
}
