#include "FirstMenu.h"
#include "Game.h"
#include "TextureManager.h"
#include "FontManager.h"
#include "LevelSelectorMenu.h"
#include "MenuOption.h"
#include "SoundManager.h"

#define DEAD_ZONE 50.0f

FirstMenu::FirstMenu()
{

	texts = vector<TextData*>();

	background = new Sprite();
	font = new Font();

	icons = vector<Shape*>();

	canClick = true;
	currentText = new TextData();

	index = 0;
	maxIndex = 0;
	hoveredIndex = -1;

	snow = new Snow(100, 50, 100);

}

FirstMenu::~FirstMenu()
{
	for (auto _text : texts)
	{
		delete _text;
	}
	for (auto _icon : icons) {
		delete _icon;
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
	vector<string> _pathIcons = { "Assets/Icons/Vide.png", "Assets/Icons/Options.png", "Assets/Icons/Retour.png" };

	vector<function<void()>> _functions =
	{
		[]() { LevelSelectorMenu::GetInstance().Show(); },
		[]() { MenuOption::GetInstance().Show(); } ,
		[]() { Game::GetInstance().GetWindow().close(); } 
	};

	for (string _name : _names) {

		texts.push_back(new TextData(_name, new Text(_name, *font, 55), false));
		icons.push_back(new RectangleShape(Vector2f(60.0f, 60.0f)));
	}

	Vector2f _pos = Vector2f(180, 400);
	int _i = 0;
	for (TextData* _text : texts) {
		_text->onClick = _functions[_i];
		_text->text->setPosition(_pos);
		_text->text->setOutlineThickness(3.0f);

		icons[_i]->setPosition(Vector2f(_pos.x - 75.0f, _pos.y));
		TextureManager::GetInstance().Load(icons[_i], _pathIcons[_i]);

		_pos.y += 100;
		_i++;
	}

	currentText = texts[0];
	currentText->text->setFillColor(Color::Red);

	maxIndex = static_cast<int>(_names.size());

}


void FirstMenu::HandleGamepadClick(Event _event)
{

		float _axisYPositionJoy = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
		int _YDirectionJoy = (_axisYPositionJoy <= -DEAD_ZONE) ? -1 : _axisYPositionJoy >= DEAD_ZONE ? 1 : 0;

		float _axisypositionFle = sf::Joystick::getAxisPosition(0, sf::Joystick::PovY);
		int _ydirectionFle = (_axisypositionFle <= -DEAD_ZONE) ? -1 : _axisypositionFle >= DEAD_ZONE ? 1 : 0;

		if (_event.type == Event::JoystickMoved) {

			if (canClick) {
				if (_YDirectionJoy == 1) {
					MoveUp();

				}
				else if (_YDirectionJoy == -1) {

					MoveDown();
				}
			}
			else if (_YDirectionJoy == 0) canClick = true;
			if (canClick) {

				if (_ydirectionFle == -1) {
					MoveUp();
				}
				else if (_ydirectionFle == 1) {
					MoveDown();
				}
				else if (_event.joystickButton.button == 0) canClick = false;
			}
		}
		if (_event.type == Event::JoystickButtonPressed) {

				if (_event.joystickButton.button == 0) {
					currentText->onClick();
				}

		}
}

void FirstMenu::MoveUp()
{
	index++;
	if (index >= maxIndex)
	{
		index--;
		return;
	}
	SoundManager::GetInstance().Play("Assets/Songs/Sounds/ui_main_roll_down.wav");
	currentText->text->setFillColor(sf::Color::White);
	currentText = texts[index];
	currentText->text->setFillColor(sf::Color::Red);
	canClick = false;
}

void FirstMenu::MoveDown()
{
	index--;
	if (index < 0)
	{
		index++;
		return;
	}
	SoundManager::GetInstance().Play("Assets/Songs/Sounds/ui_main_roll_down.wav");
	currentText->text->setFillColor(sf::Color::White);
	currentText = texts[index];
	currentText->text->setFillColor(sf::Color::Red);
	canClick = false;
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
		else if (_event.type == Event::JoystickButtonPressed || _event.type == Event::JoystickMoved)
		{

			HandleGamepadClick(_event);
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

		for (Shape* _icon : icons) {
			_window.draw(*_icon);
		}                                                                                   
		UpdateSnow();
		snow->draw(_window);

		_window.display();
	}
	return true;
}

void FirstMenu::UpdateSnow()
{
	dt = 0.f;
	dt = clock.restart().asSeconds();
	snow->update(dt);
}
