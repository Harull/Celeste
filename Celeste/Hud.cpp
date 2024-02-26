#include "Hud.h"
#include "Game.h"
#include "Macro.h"
#include "TextManager.h"
#include "Entity.h"
#include "Layers.h"

Hud::Hud()
{
	windowSize = Game::GetWindowsSize();
	InitMainMenu();
}

void Hud::InitMainMenu()
{
	RenderWindow& _window = Game::GetWindow();
	new UiData("MainMenu", windowSize, Vector2f() = windowSize / 2.f, "Assets/MenuPlay.png", [&]() {}, { ST_MENU }, false);

	new UiData("MainMenuPlay", Vector2f(windowSize.x * 15 / 100, windowSize.y * 10 / 100), Vector2f(windowSize.x * 16.5 / 100, windowSize.y * 45 / 100), "Assets/Launch.png", [&]() {Game::SetGameState(ST_MENU);	Game::SetViewState(VS_UNSCOPED); }, { ST_MENU }, false, false, true);

	new UiData("MainMenuQuit", Vector2f(windowSize.x * 10 / 100, windowSize.y * 10 / 100), Vector2f(windowSize.x * 16 / 100, windowSize.y * 60 / 100), "Assets/Quit.png", [&]() {_window.close(); }, { ST_MENU }, false, false, true);
}

void Hud::InitParamMenu()
{
	RenderWindow& _window = Game::GetWindow();
	const Vector2f& _size = Vector2f(windowSize.x * 6 / 100, windowSize.x * 6 / 100);
	const Vector2f& _position = Vector2f(windowSize.x * 96.f / 100.f, windowSize.y * 60 / 100.f);
	static const Vector2f& _paramBgSize = Vector2f(500.f, 500.f);
	static const Vector2f& _paramBgPosition = Vector2f(windowSize / 2.f);


	static const Vector2f& _exitButtonSize = Vector2f(_paramBgSize.x * 32.5f / 100.f, _paramBgPosition.y * 15 / 100);
	static const Vector2f& _exitButtonPosition = Vector2f(_paramBgPosition.x - _exitButtonSize.x, _paramBgPosition.y - _exitButtonSize.y * 2);
	static const Vector2f& _closeButtonPosition = Vector2f(_paramBgPosition.x + _paramBgPosition.x * 20.f / 100.f, _paramBgPosition.y - _paramBgPosition.y * 40.f / 100.f);;
	static const float _sizeCloseButton = 25;

	new UiData(BACKGROUND + "ParamUncloseable", _size, _position, "Assets/param.png", [&]() {
		CloseAll();
		CloseAllText();
		new UiData(MIDLE_GROUND + "BGParam", _paramBgSize, _paramBgPosition, "Assets/parchemin.png", [&]() {; }, { ST_VILLAGE }, false, false, false);
		new UiData(FOREGROUND + "ExitButton", _exitButtonSize, _paramBgPosition, "Assets/Leave.Png", [&]() {_window.close(); }, { ST_VILLAGE, }, false, false, true);
		new UiData(FOREGROUND + "SecondCloseButton", _sizeCloseButton, _closeButtonPosition, "Assets/Exit.Png", [&]() {CloseAll(); }, { ST_VILLAGE, }, false, false, true);
		}, { ST_VILLAGE }, false, false, true);
}

void Hud::CloseWithId(const vector<string>& _ids)
{
	UiManager::GetInstance().CloseWithId(_ids);
}

void Hud::CloseAll()
{
	UiManager::GetInstance().CloseAll();
}

void Hud::CloseAllText()
{
	TextManager::GetInstance().CloseAll();
}

