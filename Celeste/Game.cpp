#include "Game.h"
#include "EventReactionManager.h"
#include "EntityManager.h"

Game::Game()
{
	map = nullptr;
	player = new Player();
}

Game::~Game()
{
	if (map) delete map;
	//delete player;
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
		UpdateEvents();
		EntityManager::GetInstance().Update();
		UpdateWindow();

	}
}

void Game::UpdateWindow()
{
	window.clear(sf::Color::Black);

	std::vector<Entity*> _entities = EntityManager::GetInstance().GetAllValues();
	for (Entity* _entity : _entities)
	{
		window.draw(*_entity->GetShape());
	}


	if (map) {
		for (vector<SmallMap*> _smallMap : map->GetMaps()) {
			for (SmallMap* _sMap : _smallMap) {
				for (Drawable* _drawable : _sMap->GetGrid()->GetDrawablesMap()) {
					window.draw(*_drawable);
				}
			}
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

		EventReactionManager::Update(_event);

	}
}
