#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Player.h"
#include "Singleton.h"
#include "Menu.h"
#include "FirstMenu.h"
#include "MusicManager.h"
#include "Snow.h"

using namespace sf;

class Game : public Singleton<Game>
{
	RenderWindow window;
	Map* map;
	Player* player;
	FloatRect visibleArea;
	Menu* menu;
	MusicManager* musicManager;
	Snow* snow;
    sf::Clock clock;
	float dt;

public:
	Vector2u GetWindowSize()
	{
		return window.getSize();
	}
	Player* GetPlayer()
	{
		return player;
	}
	RenderWindow& GetWindow() {
		return window;
	}


public:
	Game();
	~Game();

public:
	void Launch();
	void UpdateWindow();
	void SelectLevel(const int _value);
	void Resume();

private:
	void Start();
	void Stop();
	void InitWindow();
	void InitMenu();
	void InitMap(const int _value);
	void InitInput();
	bool ShowOptionsInGame(const Event& _event);
	void InitPlayer();
	void Update();
	void UpdateVisibleArea();
	void UpdateEvents();


};

