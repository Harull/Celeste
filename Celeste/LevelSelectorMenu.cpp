#include "LevelSelectorMenu.h"
#include "Game.h"
#include "TextureManager.h"
#include "FontManager.h"
#include "Macro.h"
#include "TimerManager.h"
#include "MenuOption.h"
#include "MusicManager.h"

#define DEAD_ZONE 50.0f

LevelSelectorMenu::LevelSelectorMenu()
{
	background = nullptr;
	backgroundPath = vector<string>();
	font = nullptr;
	timer = nullptr;
	currentLevel = 0;
	currentAlpha = 255.0f;
	alphaFactor = 3.f;
	canClick = true;

	index = 0;
	maxIndex = 0;
}

LevelSelectorMenu::~LevelSelectorMenu()
{
	delete background;
	delete font;
	if (timer) timer->SetToRemove(true);
	if (timer2) timer2->SetToRemove(true);

}

void LevelSelectorMenu::Init(const int _levelCounts)
{
	Vector2u _windowSize = Game::GetInstance().GetWindowSize();


	for (int _i = 0; _i < _levelCounts; ++_i)
	{
		backgroundPath.push_back("Assets/Background/game_selector_background" + std::to_string(_i + 1) + ".png");
	}

	background = new RectangleShape(Vector2f(1920.0f, 1080.0f));
	TextureManager::GetInstance().Load(background, backgroundPath[0]);
	font = new Font();
	if (!font->loadFromFile("Assets/Fonts/Renogare.otf"))
	{
		cerr << "ERROR - Font non charge" << endl;
	}

	maxIndex = _levelCounts;
}

void LevelSelectorMenu::HandleGamepadClick(Event _event)
{
	float _axisYPositionJoy = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
	int _YDirectionJoy = (_axisYPositionJoy <= -DEAD_ZONE) ? -1 : _axisYPositionJoy >= DEAD_ZONE ? 1 : 0;

	float _axisypositionFle = sf::Joystick::getAxisPosition(0, sf::Joystick::PovX);
	int _ydirectionFle = (_axisypositionFle <= -DEAD_ZONE) ? -1 : _axisypositionFle >= DEAD_ZONE ? 1 : 0;

	if (!canClick) return;

	if (_event.type == Event::JoystickMoved) {

		if (_YDirectionJoy == 1) {
			if (!MoveRight()) return;
		}
		else if (_YDirectionJoy == -1) {
			if (!MoveLeft()) return;
		}
		else if (_YDirectionJoy == 0) canClick = true;

		if (!canClick) return;

		if (_ydirectionFle == 1) {
			if (!MoveRight()) return;
		}
		else if (_ydirectionFle == -1) {
			if (!MoveLeft()) return;
		}
		else if (_ydirectionFle == 0) canClick = true;
	}

	if (!canClick) return;

	if (_event.type == Event::JoystickButtonPressed) {
		if (_event.joystickButton.button == 0) {
			MenuOption::GetInstance().SetInGame(true);
			Game::GetInstance().SelectLevel(currentLevel + 1);
			MusicManager::GetInstance().Play("Sounds/SoundSelector.mp3");

		}
		else if (_event.joystickButton.button == 1) {
			FirstMenu::GetInstance().Show();
		}
	}
}

bool LevelSelectorMenu::MoveRight()
{
	index++;
	if (index >= maxIndex)
	{
		index--;
		return false;
	}
	nextPath = backgroundPath[index];
	TransitionFill();
	currentLevel = index;
	return true;

}

bool LevelSelectorMenu::MoveLeft()
{
	index--;
	if (index < 0)
	{
		index++;
		return false;
	}
	nextPath = backgroundPath[index];
	TransitionFill();
	currentLevel = index;
	return true;
}

void LevelSelectorMenu::HandleEvents(RenderWindow& _window)
{
	Event _event;
	while (_window.pollEvent(_event))
	{
		if (_event.type == Event::Closed)
		{
			_window.close();
		}
		else if (_event.type == Event::JoystickButtonPressed || _event.type == Event::JoystickMoved)
		{
			HandleGamepadClick(_event);
		}
	}
}

bool LevelSelectorMenu::Show()
{
	RenderWindow& _window = Game::GetInstance().GetWindow();
	while (_window.isOpen())
	{
		TimerManager::GetInstance().Update();
		HandleEvents(_window);

		const View _view(FloatRect(Vector2f(0.0f, 0.0f), Vector2f(1920.0f, 1080.0f)));
		_window.setView(_view);
		_window.clear();
		_window.draw(*background);
		_window.display();
	}
	return true;
}

void LevelSelectorMenu::TransitionFill() {
	canClick = false;
	const std::function<void()>& _callback = [&]() {

		Fade(background, (unsigned int)currentAlpha);

		currentAlpha -= alphaFactor;
		if (currentAlpha <= 0 || currentAlpha >= 255)
		{
			timer->Pause();
			timer->Reset();
			TextureManager::GetInstance().Load(background, nextPath);
			TransitionUnFill();

		}};
	timer = new Timer("FadeTimer", _callback, sf::seconds(0.01f), true, true);
}



void LevelSelectorMenu::TransitionUnFill()
{
	const std::function<void()>& _callback2 = [&]() {
		Fade(background, (unsigned int)currentAlpha);

		currentAlpha += alphaFactor;
		if (currentAlpha <= 0 || currentAlpha >= 255)
		{
			timer2->Pause();
			timer2->Reset();
			canClick = true;
		}};
	timer2 = new Timer("FadeTimer2", _callback2, sf::seconds(0.01f), true, true);
}