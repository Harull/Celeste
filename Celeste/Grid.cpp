#include "Grid.h"
#include "Game.h"
#include "MapManager.h"
#include "Spike.h"
#include "Strawberry.h"
#include"FragileTile.h"
#include "Macro.h"
#include "MovingTile.h"
#include"CheckPoint.h"
#include "EasterEgg.h"
#include "GemDash.h"
#include "FragileWallTile.h"
#include "OneDirectionTile.h"
#include "TextureManager.h"
#include "TileEnd.h"
#include"FallingTile.h"
#include "Tile.h"
#include"GravityTile.h"

vector<Tile*> Grid::GetTilesMap()
{
	vector<Tile*> _newTiles;

	for (vector<Tile*> _tiles : tiles)
	{
		_newTiles.insert(_newTiles.end(), _tiles.begin(), _tiles.end());
	}

	return _newTiles;
}

vector<Drawable*> Grid::GetDrawablesMap()
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

vector<Shape*> Grid::GetShapesMap()
{
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


Grid::Grid(const Vector2i _tilesCount)
{
	tilesCount = _tilesCount;
	tileSize = Vector2f(50.0f, 50.0f);
	tiles = vector<vector<Tile*>>();
	spawnPosition = Vector2f();
	gridForLoad = vector<vector<char>>();
}


void Grid::InitMap(const int _level, const int _value, Vector2f _startPos)
{
	tileSize = Vector2f(48.0f, 48.0f);
	const string _pathMap = "Maps/Level" + to_string(_level) + "/Map" + to_string(_value) + ".txt";
	StreamManager::GetInstance().LoadSmallMap(gridForLoad, _pathMap);

	string _pathBack;

	for (const char& _char : gridForLoad[0]) {
		_pathBack += _char;
	}
	new Entity({ S_APPEND("0Background"), ENTITY_NONE, sf::Vector2f(_startPos.x , _startPos.y + 48.f), Vector2f(tileSize.x * 40.0f, tileSize.y * 22.0f), _pathBack });

	string _path;
	vector<Tile*> _tiles;
	vector<string> _test;
	int _indexRow = 0, _indexColumn = 0;
	EntityType _type;
	vector<Vector2f> _positionsmouv = vector<Vector2f>();
	

	gridForLoad.erase(gridForLoad.begin());
	for (const vector<char>& _vChar : gridForLoad) {
		_indexColumn++;
		for (const char& _char : _vChar) {
			Tile* _tile;
			const float _posX = static_cast<float>(_indexRow * tileSize.x + _startPos.x);
			const float _posY = static_cast<float>(_indexColumn * tileSize.y + _startPos.y);

			if (_char == '1')
			{
				_path = "";
				_type = ENTITY_TILE;
				_tile = new Tile(_type, Vector2f(_posX, _posY), tileSize, _path, this);
			}
			else if (_char == 'I')
			{
				_path = "";
				_type = ENTITY_TILE;
				_tile = new Tile(_type, Vector2f(_posX, _posY), tileSize, _path, this);
			}
			else if (_char == '2')
			{
				_path = "Assets/SpikeTop.png";
				_type = ENTITY_TILE;
				_tile = new Spike(Vector2f(_posX, _posY), tileSize, _path, ENTITY_TILE, this);
			}
			else if (_char == '3')
			{
				_tile = new Strawberry(Vector2f(_posX, _posY), tileSize, this);
				/*_tiles.push_back(new Strawberry(Vector2f(_posX, _posY), tileSize));
				_indexRow++;*/
				//continue;
			}
			else if (_char == '4')
			{
				_tile = new EasterEgg(Vector2f(_posX, _posY), tileSize, this);
			}
			else if (_char == 'g')
			{
				_tile = new GemDash(Vector2f(_posX, _posY), tileSize, this);
			}
			else if (_char == 'x')
			{
				_path = "Assets/Avoir.png";
				_type = ENTITY_TILE;
				_tile = new Tile(_type, Vector2f(_posX, _posY), tileSize, _path, this);
			}
			else if (_char == 'c')
			{
				_path = "Assets/Vide.png";
				_type = ENTITY_CHECKPOINT;
				_tile = new CheckPoint(_type, Vector2f(_posX, _posY), tileSize, _path, this);
			}
			else if (_char == 'F')
			{
				_path = "Assets/Vide.png";
				_type = ENTITY_TILE_END;
				_tile = new TileEnd(_type, Vector2f(_posX, _posY), tileSize, _path, this);
			}
			else if (_char == 'f')
			{
				_path = "Assets/FragileTile.png";
				_type = ENTITY_TILE;
				_tile = new FragileTile(_type, Vector2f(_posX, _posY), tileSize, _path, this);
			}
			else if (_char == 'w')
			{
				_path = "";
				_type = ENTITY_TILE;
				_tile = new FragileWallTile(_type, Vector2f(_posX, _posY), tileSize, _path, this);
			}
			else if (_char == 's')
			{
				_path = "Assets/WoodPlank.png";
				_type = ENTITY_TILE;
				_tile = new OneDirectionTile(_type, Vector2f(_posX, _posY), tileSize, _path, this);
			}
			else if (_char == 'm')
			{
				_path = "Assets/MovingTile.png";
				_type = ENTITY_TILE;
				_tile = new MovingTile(_type, Vector2f(_posX, _posY), tileSize, _path, this);

			}
			else if (_char == 't')
			{
				_path = "";
				_type = ENTITY_FALLING_TILE;
				_tile = new FallingTile(_type, Vector2f(_posX, _posY), tileSize, _path, this);
			}
			else if (_char == 'd')
			{
				_positionsmouv.push_back(Vector2f(_posX, _posY));
				
				_tile = nullptr;
			}
			else if (_char == 'G')
			{
				_path = "";
				_type = ENTITY_TILE;
				_tile = new GravityTile(_type, Vector2f(_posX, _posY), tileSize, _path, this);
			}

			else
			{
				_tile = nullptr;
				tilePositionsEmpty.push_back(Vector2f(_posX, _posY));
			}
			_tiles.push_back(_tile);
			_indexRow++;

		}
		_indexRow = 0;
		tiles.push_back(_tiles);
		_tiles.clear();
	}
	for (vector<Tile*> _tilesStocked : tiles)
	{

		for (Tile* _tileStocked : _tilesStocked)
		{

			if (MovingTile* _moveTile = dynamic_cast<MovingTile*>(_tileStocked))
			{
				for (Vector2f _destination : _positionsmouv)
				{
					_moveTile->AddDestination(_destination);
				}

			}
		}
	}
	ChangeTexture();
}

void Grid::ResetAllMarks()
{
	for (auto _vect : tiles)
	{
		for (auto _value : _vect)
		{
			if (_value)
			{
				_value->SetIsMarkedByGetStackOfTypeArroundTile(false);
			}
		}
	}
}


void Grid::ChangeTexture() {

	for (int _i = 0; _i < gridForLoad.size(); ++_i) {
		for (int _j = 0; _j < gridForLoad[_i].size(); ++_j) {
			char _currentTileChar = gridForLoad[_i][_j];

			switch (_currentTileChar)
			{
			case '1':
				break;
			case 't':
				tiles[_i][_j]->GetShape()->setFillColor(sf::Color(200, 203, 203, 255));
				break;
			case 'w':
				break;
			case 'I':
				tiles[_i][_j]->GetShape()->setFillColor(sf::Color(79, 30, 19, 255));
				break;
			default:
				continue;
			}
			FinalMap(_i, _j, _currentTileChar);
		}
	}
}


void Grid::FinalMap(const int _i, const int _j, const char _char) {

	bool _isEmptyTop;
	if (_i - 1 < 0) _isEmptyTop = false;
	else
	{
		_isEmptyTop = (gridForLoad[_i - 1][_j] != _char);
	}

	bool _isEmptyDown;
	if (_i + 1 > gridForLoad.size() - 1) _isEmptyDown = false;
	else
	{
		_isEmptyDown = (gridForLoad[_i + 1][_j] != _char);
	}

	bool _isEmptyLeft;
	if (_j - 1 < 0) _isEmptyLeft = false;
	else
	{
		_isEmptyLeft = (gridForLoad[_i][_j - 1] != _char);
	}

	bool _isEmptyRight;
	if (_j + 1 > gridForLoad[_i].size() - 1) _isEmptyRight = false;
	else
	{
		_isEmptyRight = (gridForLoad[_i][_j + 1] != _char);
	}

	if (_isEmptyDown && _isEmptyTop && _isEmptyLeft && _isEmptyRight) {
		TextureManager::GetInstance().Load(tiles[_i][_j]->GetShape(), "Assets/Snow/PleinBlock.png");
	}

	else if (_isEmptyDown && _isEmptyTop && _isEmptyLeft) {
		TextureManager::GetInstance().Load(tiles[_i][_j]->GetShape(), "Assets/Snow/HautGaucheBas.png");
	}
	else if (_isEmptyDown && _isEmptyTop && _isEmptyRight) {
		TextureManager::GetInstance().Load(tiles[_i][_j]->GetShape(), "Assets/Snow/HautDroiteBas.png");
	}

	else if (_isEmptyTop && _isEmptyLeft && _isEmptyRight) {
		TextureManager::GetInstance().Load(tiles[_i][_j]->GetShape(), "Assets/Snow/GaucheHautDroit.png");
	}
	else if (_isEmptyDown && _isEmptyLeft && _isEmptyRight) {
		TextureManager::GetInstance().Load(tiles[_i][_j]->GetShape(), "Assets/Snow/GaucheDroiteBas.png");
	}

	else if (_isEmptyDown && _isEmptyTop) {
		TextureManager::GetInstance().Load(tiles[_i][_j]->GetShape(), "Assets/Snow/HautBas.png");
	}
	else if (_isEmptyLeft && _isEmptyRight) {
		TextureManager::GetInstance().Load(tiles[_i][_j]->GetShape(), "Assets/Snow/GaucheDroite.png");
	}


	else if (_isEmptyDown && _isEmptyLeft) {
		TextureManager::GetInstance().Load(tiles[_i][_j]->GetShape(), "Assets/Snow/CoinBasGauche.png");
	}
	else if (_isEmptyDown && _isEmptyRight) {
		TextureManager::GetInstance().Load(tiles[_i][_j]->GetShape(), "Assets/Snow/CoinBasDroit.png");
	}

	else if (_isEmptyTop && _isEmptyLeft) {
		TextureManager::GetInstance().Load(tiles[_i][_j]->GetShape(), "Assets/Snow/CoinHautGauche.png");
	}
	else if (_isEmptyTop && _isEmptyRight) {
		TextureManager::GetInstance().Load(tiles[_i][_j]->GetShape(), "Assets/Snow/CoinHautDroit.png");
	}
	else if (_isEmptyDown ) {
		TextureManager::GetInstance().Load(tiles[_i][_j]->GetShape(), "Assets/Snow/SnowPlafon.png");
	}
	else if (_isEmptyTop) {
		TextureManager::GetInstance().Load(tiles[_i][_j]->GetShape(), "Assets/Snow/SnowSol.png");
	}
	else if(_isEmptyLeft)
	{
		TextureManager::GetInstance().Load(tiles[_i][_j]->GetShape(), "Assets/Snow/SnowGauche.png");
	}
	else if (_isEmptyRight)
	{
		TextureManager::GetInstance().Load(tiles[_i][_j]->GetShape(), "Assets/Snow/SnowDroite.png");
	}
	else {
		TextureManager::GetInstance().Load(tiles[_i][_j]->GetShape(), "Assets/Snow/PleinBlock.png");
	}
}

bool Grid::IsIndexValid(const std::pair<int, int> _index)
{
	if (_index.first < 0 || _index.second < 0)return false;
	if (_index.first >= tiles.size()) return false;
	if (_index.second >= tiles[_index.first].size()) return false;
	return true;
}
