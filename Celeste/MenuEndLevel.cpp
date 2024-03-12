#include "MenuEndLevel.h"
#include "Game.h"
#include "TextureManager.h"
#include "FontManager.h"
#include "Macro.h"
#include "TimerManager.h"
#include "MenuOption.h"
#include "SoundManager.h"
#include "LevelSelectorMenu.h"

#define DEAD_ZONE 50.0f
#define PATH(name) "Assets/Background/End/" + to_string(name) + ".png"

MenuEndLevel::MenuEndLevel()
{
	text = nullptr;
	names = vector<string>();
	font = nullptr;
	timer = nullptr;
	currentLevel = 0;
	currentAlpha = 255.0f;
	alphaFactor = 3.f;
	canClick = false;
	background = nullptr;

	index = 0;
	maxIndex = 0;
}

MenuEndLevel::~MenuEndLevel()
{
	delete text;
	delete font;
	delete background;
	if (timer) timer->SetToRemove(true);
	if (timer2) timer2->SetToRemove(true);
	if (timerSound) timerSound->SetToRemove(true);

}

void MenuEndLevel::Init()
{
	Vector2u _windowSize = Game::GetInstance().GetWindowSize();

	font = new Font();
	if (!font->loadFromFile("Assets/Fonts/Renogare.otf"))
	{
		cerr << "ERROR - Font non charge" << endl;
	}

	names = { "Bravo !", "Tu as fini !", "Mais tu es vraiment nul" };

	text = new TextData(names[index], new Text(names[index], *font, 55), false);
	text->text->setOutlineThickness(3.0f);
	SetOriginAtMiddle(*text->text);
	text->text->setPosition(_windowSize.x / 2.0f, _windowSize.y / 2.0f);
	background = new RectangleShape(Vector2f(1920.0f, 1080.0f));
	TextureManager::GetInstance().Load(background, PATH(1));

}

void MenuEndLevel::HandleGamepadClick(Event _event)
{

	if (!canClick) return;

	if (_event.type == Event::JoystickButtonPressed) {
		if (_event.joystickButton.button == 0) {

			SoundManager::GetInstance().Play("SoundSelector.mp3");
			index++;
			if (index > maxIndex) {
				index = 0;
				text->text->setString(names[index]);
				SetOriginAtMiddle(*text->text);
				canClick = false;
				names.pop_back();
				LevelSelectorMenu::GetInstance().Show(); 
			}

			TransitionFill();

		}
	}
}



void MenuEndLevel::HandleEvents(RenderWindow& _window)
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

bool MenuEndLevel::Show()
{
	SoundManager::GetInstance().Play("cassette_get.wav");
	timerSound = new Timer("CassetteTimer", [&]() { canClick = true; }, sf::seconds(2.f), true,false);
	RenderWindow& _window = Game::GetInstance().GetWindow();
	names.push_back(Game::GetInstance().GetStopwatch()->stopwatchText);
	maxIndex = static_cast<int>(names.size() - 1);
	TextureManager::GetInstance().Load(background, PATH(RandomMaxMin(7)));

	while (_window.isOpen())
	{
		TimerManager::GetInstance().Update();
		HandleEvents(_window);

		const View _view(FloatRect(Vector2f(0.0f, 0.0f), Vector2f(1920.0f, 1080.0f)));
		_window.setView(_view);
		_window.clear();
		_window.draw(*background);
		_window.draw(*text->text);

		_window.display();
	}
	return true;
}

void MenuEndLevel::TransitionFill() {
	canClick = false;
	const std::function<void()>& _callback = [&]() {

		Fade(text->text, (unsigned int)currentAlpha);
		FadeOutlineColor(text->text, (unsigned int)currentAlpha);
	

		currentAlpha -= alphaFactor;
		if (currentAlpha <= 0 || currentAlpha >= 255)
		{
			timer->Pause();
			timer->Reset();
			text->text->setString(names[index]);
			SetOriginAtMiddle(*text->text);
			TransitionUnFill();

		}};
	timer = new Timer("FadeTimer", _callback, sf::seconds(0.01f), true, true);
}



void MenuEndLevel::TransitionUnFill()
{
	const std::function<void()>& _callback2 = [&]() {
		Fade(text->text, (unsigned int)currentAlpha);
		FadeOutlineColor(text->text, (unsigned int)currentAlpha);

		currentAlpha += alphaFactor;
		if (currentAlpha <= 0 || currentAlpha >= 255)
		{
			timer2->Pause();
			timer2->Reset();
			canClick = true;
		}};
	timer2 = new Timer("FadeTimer2", _callback2, sf::seconds(0.01f), true, true);
}