#include "Game.h"
#include "EventReactionManager.h"
#include "EntityManager.h"
#include"TimerManager.h"
#include"Camera.h"
#include "FirstMenu.h"
#include "LevelSelectorMenu.h"
#include "MenuOption.h"
#include "MapManager.h"
#include "AnimationComponent.h"
#include "MenuSoundBoard.h"
#include "SoundManager.h"
#include "MenuEndLevel.h"
#include "TimerManager.h"
#include"TextureManager.h"
#include"Portal.h"
#include"LoadingLogo.h"
#include "MenuSoundBoard.h"


#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define FPS(x) sf::sleep(sf::seconds(1.f / x) - _clock.getElapsedTime())

Game::Game() 
{
	map = nullptr;
	player = nullptr;
	visibleArea = FloatRect();
	snow = new Snow(100, 50, 100);
	senseOfGravity = GRAVITY_NORMAL;
	stopwatch = new Stopwatch();
	loadingScreen = new RectangleShape({ 1920 ,1080 });
	loadingScreen->setPosition({ 0.f,0.f });
}

Game::~Game()
{
	delete player;
	delete snow;
	delete stopwatch;
}

void Game::Launch()
{
	Start();
	Stop();
}

void Game::Start()
{
	TextureManager::GetInstance().Load(loadingScreen, "Assets/Texture/Madeline.png");
	InitWindow();
	InitMenu();
	MusicManager::GetInstance().Play("Celeste_OST.mp3");
	MusicManager::GetInstance().SetVolume(20.f);

	FirstMenu::GetInstance().Show();
	
}

void Game::InitMenu()
{
	FirstMenu::GetInstance().Init();
	LevelSelectorMenu::GetInstance().Init(6);
	MenuOption::GetInstance().Init();
	MenuSoundBoard::GetInstance().Init();
	MenuEndLevel::GetInstance().Init();

}

void Game::InitMap(const int _value)
{
	SoundManager::GetInstance().Play("SoundSelector.mp3");
	MapManager::GetInstance().Clear();
	EntityManager::GetInstance().Clear();
	EventReactionManager::Clear();
	
	delete player;
	player = new Player();
	map = new Map();

	map->Init(_value);
	InitInput();
	Camera::GetInstance().Update(true);
	new Timer("Loading", [this]() {}, seconds(15));
	Vector2f _logoPosition = Vector2f(window.getSize().x * 0.95, window.getSize().y * 0.9);
	LoadingLogo* _loadingImage = new  LoadingLogo(_logoPosition);
	while (TimerManager::GetInstance().GetApproximately("Loading"))
	{
		TimerManager::GetInstance().Update();
		_loadingImage->Update();
		UpdateWindow(true);
	}
	_loadingImage->SetToRemove(true);
	Update();
}

void Game::InitInput()
{
	EventReactionManager::BindNewInputReaction(sf::Event::JoystickButtonPressed, [&](const Event& _event) {
		if (_event.joystickButton.button == 7)
			return MenuOption::GetInstance().Show();
		return false;
		});

	EventReactionManager::BindNewInputReaction(sf::Event::JoystickButtonPressed, [&](const Event& _event) {
		if (_event.joystickButton.button == 6)
			return MenuSoundBoard::GetInstance().Show();
		return false;
		});

	EventReactionManager::BindNewInputReaction(sf::Event::KeyPressed, [&](const Event& _event){
		if (_event.key.code == sf::Keyboard::M)
		{
			ToggleSenseOfGravity();
			return true;
		}
		return false;
		});
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

	Camera::GetInstance().Init({ 0,0 }, { 1920, 1080 - 24 }); // -24 c'est - la moitié d'un bloc
	stopwatch->Init();
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
		if (!window.isOpen())
			return;

		EntityManager::GetInstance().Update();
		TimerManager::GetInstance().Update();
		Camera::GetInstance().Update();
		UpdateWindow();
		UpdateSnow();
		stopwatch->Update();

		FPS(144);
		if (player->GetCharacter()->GetHasWon())
		{
			MenuOption::GetInstance().SetInGame(false);
			TimerManager::GetInstance().DeleteAll();
			MenuEndLevel::GetInstance().Show();
		}
	}
}

void Game::UpdateVisibleArea()
{
	visibleArea = FloatRect(Camera::GetInstance().getCenter() - Camera::GetInstance().getSize() / 2.0f, Camera::GetInstance().getSize());
}

void Game::UpdateWindow(bool _loading)
{
	if (_loading)
	{

		window.clear();
		Sprite* _sprite =EntityManager::GetInstance().GetApproximately("LoadingLogo")->GetComponent<AnimationComponent>()->GetCurrentAnimation()->GetSprite();
		window.draw(*_sprite);
		window.draw(*loadingScreen);
		window.display();
		return;
	}
	window.clear(sf::Color::Black);
	UpdateVisibleArea();
	window.setView(Camera::GetInstance());

	std::vector<Drawable*> _entities = EntityManager::GetInstance().GetDrawables(visibleArea);
	for (Drawable* _entity : _entities)
	{
		window.draw(*_entity);
	}

	window.setView(window.getDefaultView());

	window.draw(*stopwatch->text);

	snow->draw(window);
	window.display();
}

void Game::SelectLevel(const int _value)
{
	MenuOption::GetInstance().SetInGame(true);
	InitMap(_value);
}

void Game::Resume()
{
	if (!window.isOpen())return;
	Update();
}

void Game::UpdateEvents()
{
	sf::Event _event;
	while (window.pollEvent(_event))
	{
		if (_event.type == sf::Event::Closed)
			Stop();
		else {
			EventReactionManager::Update(_event);
		}
	}
}

void Game::UpdateSnow()
{
	dt = 0.f;
	dt = clock.restart().asSeconds();
	snow->update(dt);
}



