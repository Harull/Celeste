#include "MenuSoundBoard.h"
#include "Game.h"
#include "TextureManager.h"
#include "FontManager.h"
#include "Macro.h"
#include "SoundManager.h"
#include "SoundManager.h"
#include "MenuOption.h"

#define PATH(name) "Assets/Songs/SoundBoard/" + string(name) + ".mp3"

MenuSoundBoard::MenuSoundBoard()
{
	buttons = vector<Text*>();
	back = new Text();
	background = nullptr;
	font = nullptr;
	positions = vector<Vector2f>();
	index = 0;
	forMouse = nullptr;
	maxValue = 10;

}

MenuSoundBoard::~MenuSoundBoard()
{
	for (auto _button : buttons) {
		delete _button;
	}
	delete forMouse;
	delete background;
	delete back;

}

void MenuSoundBoard::Init()
{
	Vector2u _windowSize = Game::GetInstance().GetWindowSize();


	background = new RectangleShape(Vector2f(1920.0f, 1080.0f));



	TextureManager::GetInstance().Load(background, "Assets/Background/celeste_background.png");

	font = new Font();
	if (!font->loadFromFile("Assets/Fonts/Renogare.otf"))
	{
		cerr << "ERROR - Font non charge" << endl;
	}

	float _posX = (_windowSize.x - 500.0f) / 2;
	float _sizeY = 50.0f;
	float _posY = (_windowSize.y - _sizeY * maxValue) / 2;
	forMouse = new RectangleShape(Vector2f(500.0f, (_sizeY * maxValue) + 15.0f));
	forMouse->setPosition(_posX, _posY);
	forMouse->setFillColor(Color(0, 0, 0, 120));
	forMouse->setOutlineThickness(5.0f);

	for (int _i = 0; _i < maxValue; _i++) {
		positions.push_back(Vector2f(_posX, _posY));
		_posY += 50.0f;
	}



	vector<string> _nameSongs = {
	   "anotherone",
	   "chipi",
	   "door",
	   "lol",
	   "pew",
	   "rehehehe",
	   "scoobysnacks",
	   "spy",
	   "tacobell",
	   "uwu",
	   "windows",
	   "yeahboi",
	   "yippie",
	};

	for (string _nameSong : _nameSongs) {
		paths.push_back(PATH(_nameSong));
		buttons.push_back(new Text(_nameSong, *font, 50));
	}
	back->setString("Back");
	back->setFont(*font);
	back->setPosition(0, 1000);


	Vector2f _startPosition = Vector2f(0.0f, 100.0f);

	for (Text* _button : buttons)
	{
		_button->setFont(*font);
		_startPosition.y += 100;
	}

}

void MenuSoundBoard::HandleMouseClick(Mouse::Button _button, const Vector2i& _mousePosition, RenderWindow& _window)
{

	if (_button == Mouse::Left)
	{

		for (int _i = 0; _i < buttons.size(); _i++) {
			if (buttons[_i]->getGlobalBounds().contains((float)_mousePosition.x, (float)_mousePosition.y))
			{
				SoundManager::GetInstance().Play(paths[_i]);
			}
		}

		if (back->getGlobalBounds().contains((float)_mousePosition.x, (float)_mousePosition.y)) {
			MenuOption::GetInstance().Show();
		}
	}
}

void MenuSoundBoard::HandleMouseScroll(const float _delta, const Vector2i& _mousePosition, RenderWindow& _window)
{

	if (forMouse->getGlobalBounds().contains((float)_mousePosition.x, (float)_mousePosition.y)) {
		if (_delta > 0) {
			index--;
			if (index == -1) {
				index++;
			}
		}
		else if (_delta < 0) {
			index++;
			if (index == buttons.size() - maxValue + 1 ) {
				index--;
			}
		}

	}
}

void MenuSoundBoard::HandleKeyboardClick(Keyboard::Scancode _button) {

	if (_button == sf::Keyboard::C) {

	}
	if (_button == sf::Keyboard::X) {

	}
}

void MenuSoundBoard::HandleEvents(RenderWindow& _window)
{
	Event _event;
	while (_window.pollEvent(_event))
	{

		if (_event.type == Event::Closed)
		{
			_window.close();
		}
		else if (_event.type == Event::MouseButtonPressed)
		{
			HandleMouseClick(_event.mouseButton.button, Mouse::getPosition(_window), _window);
		}
		else if (_event.type == Event::MouseWheelScrolled)
		{
			HandleMouseScroll(_event.mouseWheelScroll.delta, Mouse::getPosition(_window), _window);
		}
		else if (_event.type == Event::KeyPressed)
		{
			HandleKeyboardClick(_event.key.scancode);
		}
	}
}

bool MenuSoundBoard::Show()
{
	RenderWindow& _window = Game::GetInstance().GetWindow();
	while (_window.isOpen())
	{
		HandleEvents(_window);

		const View _view(FloatRect(Vector2f(0.0f, 0.0f), Vector2f(1920.0f, 1080.0f)));
		_window.setView(_view);
		_window.clear();
		_window.draw(*background);
		_window.draw(*forMouse);
		_window.draw(*back);

		for (int _i = 0 + index; _i < maxValue + index; _i++)
		{
			buttons[_i]->setPosition(positions[_i - index]);
			_window.draw(*buttons[_i]);
		}

		_window.display();
	}
	return true;
}





