#include "Game.h"
#include "InputManager.h"
#include "EntityManager.h"
#include"TimerManager.h"

Game::Game()
{
	map = nullptr;
	player = new Player();
}

Game::~Game()
{
	if (map) delete map;
	delete player;
}

void Game::Launch()
{
	Start();
	Update();
	Stop();
}

void Game::Start()
{
	InitWindow();
	InitMap(1);
}

void Game::InitMap(const int _value)
{
	if (!map)
	{
		map = new Map();
	}
	map->Init(_value);
}

void Game::Stop()
{
	window.close();
}

void Game::InitWindow()
{
	window.create(VideoMode(1280, 720), "Celeste");
}

void Game::InitPlayer()
{
}

void Game::Update()
{
	while (window.isOpen())
	{
		if (!InputManager::GetInstance().UpdateWindow(window))break;
		EntityManager::GetInstance().Update();
		TimerManager::GetInstance().Update();
		UpdateWindow();
	}
}





void Game::UpdateWindow()
{
	window.clear();
	if (map) {
		for (vector<SmallMap*> _smallMap : map->GetMaps()) {
			for (SmallMap* _sMap : _smallMap) {
				for (Drawable* _drawable : _sMap->GetGrid()->GetDrawablesMap()) {
					window.draw(*_drawable);
				}
			}
		}
	}
	window.draw(*player->GetCharacter().GetShape());
	window.display();
}
