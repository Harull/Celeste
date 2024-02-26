#include "Game.h"
#include "EntityManager.h"
#include "TimerManager.h"
#include "InputManager.h"
#include "TextManager.h"
#include "UiManager.h"
#include "Hud.h"



RenderWindow Game::mainWindow;
GameState Game::state;
Player* Game::player;
View* Game::currentView;
View Game::unscopedView;
View Game::scopedView;
ViewState Game::viewState;

Game::Game()
{
	player = nullptr;
	hud = nullptr;
	state = ST_MENU;
	currentView = new View();
	unscopedView = View();
	scopedView = View();
}

Game::~Game()
{
	delete player;
	player = nullptr;
	delete hud;
	hud = nullptr;
	delete currentView;
	currentView = nullptr;

}

void Game::Launch()
{
	Start();
	Update();
	Stop();
}

void Game::Start()
{
	mainWindow.create(VideoMode(1920, 1080), "Celeste", (sf::Style::Resize == false) | (sf::Style::Fullscreen));
	const Vector2f& _windowSize = Vector2f(mainWindow.getSize());
	hud = new Hud();
	//TileMap* _tileMapVillage = new TileMap("TmVillage", { 0, 0 }, { 200,175 }, VILLAGE, { ST_VILLAGE }, VS_UNSCOPED);
	//TileMap* _tileMapAttack = new TileMap("TmAttack", { 0,0 }, { 200,175 }, LEVEL_ONE, { ST_ATTACK }, VS_SCOPED);

	//player = new Player(_tileMapAttack->GetTilePositionWithTile(_tileMapAttack->GetTileOnEdges().end));

	InitUnscopedView();
	InitScopedView();
	SetViewState(VS_DEFAULT);
}

void Game::InitUnscopedView()
{
	//TileMap* _tileMapVillage = TileMapManager::GetInstance().GetWithApproximateId("Village");
	//const std::vector<std::vector<Tile*>>& _currentTiles = _tileMapVillage->GetTiles();

	//const sf::Vector2f _unscopedView = { 3840 , 2160 };
	//const int _yIndex = static_cast<int>(_currentTiles.size() / 2);
	//const sf::Vector2i _tileIndex = { _yIndex, static_cast<int>(_currentTiles[_yIndex].size() / 2) };
	//const sf::Vector2f _camPosition = { _tileMapVillage->GetPositionWithIndex(_tileIndex) };
	//unscopedView = sf::View(_camPosition, _unscopedView);
}

void Game::InitScopedView()
{
	scopedView = sf::View(GetWindowsSize(), { 640, 360 });
}

void Game::UpdateViewPosition()
{
	//if (state == ST_ATTACK)
	//	currentView->setCenter(player->GetCharacter()->GetPosition());
	//Sinon if ST_VILLAGE todo faire le déplacement avec la souris;
}

void Game::UpdateCurrentView()
{
	/*delete currentView;
	currentView = nullptr;

	switch (viewState)
	{
	case VS_DEFAULT:
		currentView = new sf::View(mainWindow.getDefaultView());
		break;
	case VS_UNSCOPED:
		currentView = new sf::View(unscopedView);
		break;
	case VS_SCOPED:
		currentView = new sf::View(player->GetCharacter()->GetPosition(), scopedView.getSize());
		break;
	default:
		break;
	}
	if (currentView)
		mainWindow.setView(*currentView);
	else
		std::cerr << "Erreur UpdateCurrentView(), currentView = nullptr" << std::endl;*/
}

void Game::Update()
{
	while (mainWindow.isOpen())
	{
		EntityManager::GetInstance().Update();
		TimerManager::GetInstance().Update();
		InputManager::GetInstance().UpdateWindow(mainWindow);
		UiManager::GetInstance().Update();
		UiManager::GetInstance().GarbageValues();
		UpdateWindow();
	}
}

void Game::Stop()
{

}

void Game::UpdateWindow()
{
	//mainWindow.clear();
	//TileMapManager::GetInstance().DiplayAllTileMap();

	EntityManager::GetInstance().DisplayAllEntities();

	//SetViewState(VS_DEFAULT);
	UiManager::GetInstance().DisplayAllUi();
	TextManager::GetInstance().DisplayAllTexts();

	mainWindow.display();
}