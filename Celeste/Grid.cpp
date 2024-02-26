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
	cout << _windowSize.x << " " << _windowSize.y << endl;

	const float _startPosX = _windowSize.x * 0.35f;
	const float _startPosY = _windowSize.y * 0.1f;

	string _path;
	vector<Tile*> _tiles;
	vector<string> _test;
	int _indexRow = 0, _indexColumn = 0;
	EntityType _type;

	for (const vector<char>& _vChar : _gridForLoad) {
		_indexColumn++;
		for (const char& _char : _vChar) {

			const float _posX = static_cast<float>(_indexRow * tileSize.x + _startPosX);
			const float _posY = static_cast<float>(_indexColumn * tileSize.y + _startPosY);
			
			if (_char == '1')
			{
				_path = "Assets/1.png";
				_type = ENTITY_TILE;
			}
			else if (_char == '2')
			{
				_path = "Assets/2.png";
				_type = ENTITY_TILE;
			}
			else if (_char == '3')
			{
				_path = "Assets/3.png";
				_type = ENTITY_TILE;
			}
			else if (_char == '4')
			{
				_path = "Assets/4.png";
				_type = ENTITY_TILE;
			}
			else if (_char == '5')
			{
				_path = "Assets/5.png";
				_type = ENTITY_TILE;
			}
			else if (_char == '6')
			{
				_path = "Assets/6.png";
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
