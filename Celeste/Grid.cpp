#include "Grid.h"
#include "Game.h"
#include "MapManager.h"
#include "Strawberry.h"
#include "Macro.h"

Grid::Grid(const Vector2i _tilesCount)
{
	tilesCount = _tilesCount;
	tileSize = Vector2f(50.0f, 50.0f);
	tiles = vector<vector<Tile*>>();
	spawnPosition = Vector2f();
}


void Grid::InitMap(const int _level, const int _value, Vector2f _startPos)
{
	tileSize = Vector2f(48.0f, 48.0f);
	vector<vector<char>> _gridForLoad;
	const string _pathMap = "Maps/Level" + to_string(_level) + "/Map" + to_string(_value) + ".txt";
	StreamManager::GetInstance().LoadSmallMap(_gridForLoad, _pathMap);

	string _pathBack;

	for (const char& _char : _gridForLoad[0]) {
		_pathBack += _char;
	}
	new Entity({ S_APPEND("0Background"), ENTITY_NONE, _startPos, Vector2f(tileSize.x * 40.0f, tileSize.y * 22.0f), _pathBack });

	string _path;
	vector<Tile*> _tiles;
	vector<string> _test;
	int _indexRow = 0, _indexColumn = 0;
	EntityType _type;

	_gridForLoad.erase(_gridForLoad.begin());

	for (const vector<char>& _vChar : _gridForLoad) {
		_indexColumn++;
		for (const char& _char : _vChar) {

			const float _posX = static_cast<float>(_indexRow * tileSize.x + _startPos.x);
			const float _posY = static_cast<float>(_indexColumn * tileSize.y + _startPos.y);

			if (_char == '1')
			{
				_path = "Assets/Snow1.png";
				_type = ENTITY_TILE;
			}
			else if (_char == '2')
			{
				_path = "Assets/SpikeTop.png";
				_type = ENTITY_TILE;
			}
			else if (_char == '3')
			{
				_tiles.push_back(new Strawberry(Vector2f(_posX, _posY), tileSize));
				_indexRow++;
				continue;
			}
			else if (_char == 'x')
			{
				_path = "Assets/Avoir.png";
				_type = ENTITY_TILE;
			}
			else if (_char == 'c')
			{
				_path = "Assets/Vide.png";
				_type = ENTITY_CHECKPOINT;
			}
			else
			{
				_tiles.push_back(nullptr);
				_indexRow++;
				continue;
			}

			_tiles.push_back(new Tile(_type, Vector2f(_posX, _posY), tileSize, _path));
			_indexRow++;

		}
		_indexRow = 0;
		tiles.push_back(_tiles);
		_tiles.clear();
	}
}
