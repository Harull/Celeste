#include "Game.h"
#include "EventReactionManager.h"
#include "EntityManager.h"
#include"TimerManager.h"

Game::Game()
{
	map = nullptr;
	player = new Player();
	view = View();
	visibleArea = FloatRect();
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
		UpdateVisibleArea();
		UpdateEvents();
		EntityManager::GetInstance().Update();
		TimerManager::GetInstance().Update();
		UpdateWindow();
	}
}

void Game::UpdateVisibleArea()
{
	view = window.getView();
	visibleArea = FloatRect(view.getCenter() - view.getSize() / 2.0f, view.getSize());
}

void Game::UpdateWindow()
{
	window.clear(sf::Color::Black);

	std::vector<Entity*> _entities = EntityManager::GetInstance().GetAllValues();
	for (Entity* _entity : _entities)
	{
		if (visibleArea.intersects(_entity->GetShape()->getGlobalBounds())) {
			window.draw(*_entity->GetShape());
		}
	}

	if (map) {
		vector<Shape*> _mapShapes = map->GetShapesMap();
		for (Shape* _shape : _mapShapes) {
			if (visibleArea.intersects(_shape->getGlobalBounds())) {
				window.draw(*_shape);
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
