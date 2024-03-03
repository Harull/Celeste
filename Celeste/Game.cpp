#include "Game.h"
#include "EventReactionManager.h"
#include "EntityManager.h"
#include"TimerManager.h"
#include"Camera.h"


#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define FPS(x) sf::sleep(sf::seconds(1.f / x) - _clock.getElapsedTime())

Game::Game() 
{
	map = nullptr;
	player = new Player();
	visibleArea = FloatRect();
	menu = nullptr;
	snow = new Snow(100.0f, 50.0f, 100.0f);
}

Game::~Game()
{
	if (map) delete map;
	if (player) delete player;
	if (menu) delete menu;

}

void Game::Launch()
{
	if (!Start()) return;
	Update();
	Stop();
}

bool Game::Start()
{
	InitWindow();

	MusicManager::GetInstance().Play("Celeste_OST.mp3");
	menu = new Menu();
	int _level = 1;
	do
	{
		if (!menu->ShowMenu(window)) return false;
		_level = menu->ShowLevelSelector(window);
		cout << _level << endl;
	} while (_level == -1);
	
	delete menu;
	menu = nullptr;

	InitMap(_level);

	return true;

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
	const int _xWindowSize = 1920, _yWindowSize = 1080;
	window.create(VideoMode(_xWindowSize, _yWindowSize), "Celeste", Style::Fullscreen);
	Camera::GetInstance().Init({0,0}, { 1920, 1080 });
}

void Game::InitPlayer()
{
}

void Game::Update()
{
	sf::Clock _clock;
	while (window.isOpen())
	{
		_clock.restart();
		
		UpdateEvents();
		EntityManager::GetInstance().Update();
		TimerManager::GetInstance().Update();
		Camera::GetInstance().Update(this);
		UpdateWindow();

		FPS(120);
	}
}

void Game::UpdateVisibleArea()
{
	visibleArea = FloatRect(Camera::GetInstance().getCenter() - Camera::GetInstance().getSize() / 2.0f, Camera::GetInstance().getSize());
}

void Game::UpdateWindow()
{
	window.clear(sf::Color::Black);
	UpdateVisibleArea();
	window.setView(Camera::GetInstance());


	std::vector<Drawable*> _entities = EntityManager::GetInstance().GetDrawables(visibleArea);
	for (Drawable* _entity : _entities)
	{
			window.draw(*_entity);

	}

	dt = 0.f;
	dt = clock.restart().asSeconds();
	snow->update(dt);
	snow->draw(window);
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

