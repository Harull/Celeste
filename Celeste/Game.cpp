#include "Game.h"
#include "EventReactionManager.h"
#include "EntityManager.h"
#include"TimerManager.h"
#include"Camera.h"
#include "Menu.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

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
	Camera::GetInstance().Init(Vector2f(100.f, 100.f), Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
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
		Camera::GetInstance().Update();
		UpdateWindow();
		window.setView(Camera::GetInstance());
	}
}

void Game::UpdateVisibleArea()
{
	
	visibleArea = FloatRect(Camera::GetInstance().getCenter() - Camera::GetInstance().getSize() / 2.0f, Camera::GetInstance().getSize());
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
		else{
			EventReactionManager::Update(_event);
		}
	}
}
