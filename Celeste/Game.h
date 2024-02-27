#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Player.h"

using namespace sf;

class Game : public Singleton<Game>
{
	RenderWindow window;
	Map* map;
	Player* player;

public:
	Vector2u GetWindowSize()
	{
		return window.getSize();
	}
	Player* GetPlayer()
	{
		return player;
	}


public:
	Game();
	~Game();

public:
	void Launch();
	void InitMap(const int _value);


private:
	void Start();
	void Stop();
	void InitWindow();
	void InitPlayer();
	void Update();
	void UpdateWindow();
	void UpdateEvents();

};

