#include "Game.h"
#include "EventReactionManager.h"
#include "EntityManager.h"
#include "TimerManager.h"
#include "EventReactionManager.h"
#include "Menu.h"


Game::Game()
{
	map = nullptr;
	player = new Player();
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
	Menu _menu;
	_menu.ShowMenu(window);
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
	//window.create(VideoMode(1920, 1080), "Celeste", Style::Fullscreen);
}

void Game::InitPlayer()
{
}

void Game::Update()
{
	while (window.isOpen())
	{
		UpdateEvents();
		EntityManager::GetInstance().Update();
		TimerManager::GetInstance().Update();
		UpdateWindow();
	}
}


void Game::UpdateWindow()
{
	window.clear(sf::Color::Black);

	std::vector<Drawable*> _entities = EntityManager::GetInstance().GetDrawables();
	for (Drawable* _entity : _entities)
	{
		window.draw(*_entity);
	}

	if (map) {
		vector<Drawable*> _mapDrawables = map->GetDrawables();
		for (Drawable* _drawable : _mapDrawables) {
			window.draw(*_drawable);
		}
	}

	window.display();
}

void Game::UpdateEvents()
{
	sf::Event _event;
	while (window.pollEvent(_event))
	{
		if (_event.type == sf::Event::Closed)
			Stop();
		else{
			EventReactionManager::Update(_event);
		}
	}
}
