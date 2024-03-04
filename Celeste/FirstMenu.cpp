#include "FirstMenu.h"
#include "Game.h"
#include "TextureManager.h"
#include "FontManager.h"
#include "LevelSelectorMenu.h"
#include "MenuOption.h"

#define DEAD_ZONE 50.0f

FirstMenu::FirstMenu()
{

	texts = vector<TextData*>();

	background = new Sprite();
	font = new Font();

	index = 0;
	maxIndex = 0;
}

FirstMenu::~FirstMenu()
{

	for (auto _text : texts)
	{
		delete _text;
	}

	delete background;
	delete font;
}

void FirstMenu::Init()
{
	Vector2u _windowSize = Game::GetInstance().GetWindowSize();

	TextureManager::GetInstance().Load(background, "Assets/Background/celeste_background.png");

	background->setScale(
		static_cast<float>(_windowSize.x) / background->getLocalBounds().width,
		static_cast<float>(_windowSize.y) / background->getLocalBounds().height
	);

	if (!font->loadFromFile("Assets/Fonts/Renogare.otf"))
	{
		cerr << "ERROR - Font non charge" << endl;
	}

	vector<string> _names = { "Play", "Options", "Exit" };

	for (string _name : _names) {

		texts.push_back(new TextData(_name, new Text(_name, *font, 50)));
	}

	Vector2f _pos = Vector2f(180, 400);
	for (TextData* _text : texts) {
		_text->text->setPosition(_pos);
		_pos.y += 100;
	}

	maxIndex = _names.size();

}

void FirstMenu::HandleMouseClick(Mouse::Button _button, const Vector2i& _mousePosition, RenderWindow& _window)
{
	if (_button == Mouse::Left)
	{

		for (TextData* _text : texts) {
			if (_text->name == "Play") {
				if (_text->text->getGlobalBounds().contains(static_cast<float>(_mousePosition.x), static_cast<float>(_mousePosition.y))) {
					LevelSelectorMenu::GetInstance().Show();
				}
			}
			else if (_text->name == "Options") {
				if (_text->text->getGlobalBounds().contains(static_cast<float>(_mousePosition.x), static_cast<float>(_mousePosition.y)))
				{
					MenuOption::GetInstance().Show();
				}
			}
			else if (_text->name == "Exit") {
				if (_text->text->getGlobalBounds().contains(static_cast<float>(_mousePosition.x), static_cast<float>(_mousePosition.y)))
				{
					_window.close();
				}
			}
		}
	}
}

void FirstMenu::HandleKeyboardClick(Event _event)
{
	cout << "test" << endl;
	if (_event.type == sf::Joystick::Y) {
		float _axisYPosition = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
		int _YDirection = (_axisYPosition <= -DEAD_ZONE) ? -1 : _axisYPosition >= DEAD_ZONE ? 1 : 0;
		if (_YDirection == 1) {
			cout << "Down" << endl;
		}
		else if (_YDirection == -1) {
			cout << "Up" << endl;
		
		}

		//if ()
		//{

		//}

		//	if else() {

		//}

	}

	if (_event.joystickButton.button == sf::Joystick::PovY) {
		index++;
		cout << index << endl;
		if (index > maxIndex) index--;
		texts[index]->text->setFillColor(sf::Color::Red);

	}
	else if (_event.joystickButton.button == sf::Joystick::PovY) {
		index--;
		cout << index << endl;
		if (index < 0) index++;
		texts[index]->text->setFillColor(sf::Color::Red);

	}

}

void FirstMenu::HandleEvents(RenderWindow& _window)
{
	Event _event;
	while (_window.pollEvent(_event))
	{
		if (_event.type == Event::Closed)
		{
			_window.close();
		}
		//else if (_event.type == Event::JoystickButtonPressed)
		//{
		//	HandleKeyboardClick(_event);
		//}
		else if (_event.type == Event::MouseButtonPressed)
		{
			HandleMouseClick(_event.mouseButton.button, Mouse::getPosition(_window), _window);
		}
	}

}

bool FirstMenu::Show()
{

	RenderWindow& _window = Game::GetInstance().GetWindow();

	while (_window.isOpen())
	{
		HandleEvents(_window);

		const View _view(FloatRect(Vector2f(0.0f, 0.0f), Vector2f(1920.0f, 1080.0f)));
		_window.setView(_view);
		_window.clear();
		_window.draw(*background);

		for (TextData* _text : texts) {
			_window.draw(*_text->text);
		}

		_window.display();
	}
	return true;
}