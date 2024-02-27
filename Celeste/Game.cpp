#include "Game.h"
#include "InputManager.h"
#include "EntityManager.h"

Game::Game()
{
	map = nullptr;
	player = nullptr;
}

Game::~Game()
{
	if (map) delete map;
	if (player) delete player;
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
	//window.create(VideoMode(1280, 720), "Celeste");
	window.create(VideoMode(1920, 1080), "Celeste", Style::Fullscreen);
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
		UpdateWindow();
	}
}

void Game::UpdateWindow()
{
	window.clear(Color::Black);
	if (map) {
		for (Drawable* _drawable : map->GetDrawables()) {
			window.draw(*_drawable);
		}
	}
	window.display();
}
