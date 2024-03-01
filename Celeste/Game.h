#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Player.h"
#include "Singleton.h"
#include "Menu.h"
#include "MusicManager.h"

using namespace sf;

class Game : public Singleton<Game>
{
	RenderWindow window;
	Map* map;
	Player* player;
	FloatRect visibleArea;
	Menu* menu;
	MusicManager* musicManager;

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
	void UpdateWindow();

private:
	bool Start();
	void Stop();
	void InitWindow();
	void InitMap(const int _value);
	void InitPlayer();
	void Update();
	void UpdateVisibleArea();
	void UpdateEvents();

};

