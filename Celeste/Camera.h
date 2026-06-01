#pragma once
#include <SFML/Graphics.hpp>
#include"Singleton.h"
#include "MapManager.h"
using namespace sf;
class Game;


class Camera: public View, public Singleton<Camera>
{

	sf::Vector2i previousIndexes;
	vector<SmallMap*> mapAround;
public:
	vector<SmallMap*> GetMapsAround()const
	{
		return mapAround;
	}
public:
	void Init(const Vector2f& _position, const Vector2f& _size);
	void Update(bool _heroTeleport =false);
	void UpdateMapAround(const vector<vector<SmallMap*>>& _maps);
};

