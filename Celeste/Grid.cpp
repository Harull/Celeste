#include "Grid.h"
#include "Game.h"
#include "MapManager.h"

Grid::Grid(const Vector2i _tilesCount)
{
	tilesCount = _tilesCount;
	tileSize = Vector2f(50.0f, 50.0f);
	tiles = vector<vector<Tile*>>();
	spawnPosition = Vector2f();
}


void Grid::InitMap(const int _level, const int _value, Vector2f _startPos)
{
	//tileSize = Vector2f(16.0f, 16.0f);
	tileSize = Vector2f(48.0f, 48.0f);
	vector<vector<char>> _gridForLoad;
	const string _pathMap = "Maps/Level"+ to_string(_level) + "/Map" + to_string(_value) + ".txt";
	StreamManager::GetInstance().LoadSmallMap(_gridForLoad, _pathMap);

	string _path;
	vector<Tile*> _tiles;
	vector<string> _test;
	int _indexRow = 0, _indexColumn = 0;
	EntityType _type;

	for (const vector<char>& _vChar : _gridForLoad) {
		_indexColumn++;
		for (const char& _char : _vChar) {

			const float _posX = static_cast<float>(_indexRow * tileSize.x + _startPos.x);
			const float _posY = static_cast<float>(_indexColumn * tileSize.y + _startPos.y);

			switch (_char)
			{
			case '1':
				_path = "Assets/Snow1.png";
				_type = ENTITY_TILE;
				break;
			case '2':
				_path = "Assets/SpikeTop.png";
				_type = ENTITY_TILE;
				break;
			case 'x':
				_path = "Assets/Avoir.png";
				_type = ENTITY_TILE;
				break;
			case 'c':
				_path = "Assets/Vide.png";
				_type = ENTITY_CHECKPOINT;
			default:
				Tile* _tile = nullptr;
				_tiles.push_back(_tile);
				_indexRow++;
				continue;
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
