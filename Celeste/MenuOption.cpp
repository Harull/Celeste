#include "MenuOption.h"
#include "Game.h"
#include "TextureManager.h"
#include "FontManager.h"
#include "LevelSelectorMenu.h"
#include "MenuSoundBoard.h"
#define DEAD_ZONE 50.0f

MenuOption::MenuOption()
{
	currentVolumeCount = 2;


	background = new Sprite();
	font = new Font();

	texts = vector<TextData*>();
	canClick = true;
	currentText = new TextData();
	index = 0;
	maxIndex = 0;
	minIndex = 0;

	inGame = false;

}

MenuOption::~MenuOption()
{
	for (auto _text : texts)
	{
		delete _text;
	}

	delete background;
	delete font;
}

void MenuOption::Init()
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

	vector<string> _names =
	{
		"Resume",
		"Volume <" + to_string(currentVolumeCount) + ">",
		"SoundBoard",
		"Retour",
	};

	vector<function<void()>> _functions =
	{
		[]() { Game::GetInstance().Resume(); } ,
		[this]() { ChangeVolume(); },
		[]() { MenuSoundBoard::GetInstance().Show(); } ,
		[]() { 
			MenuOption::GetInstance().SetInGame(false);
			LevelSelectorMenu::GetInstance().Show(); 
		}
	};

	for (string _name : _names) {
		if (_name != "Resume") {
			texts.push_back(new TextData(_name, new Text(_name, *font, 50), false));
		}
		else
		{
			texts.push_back(new TextData(_name, new Text(_name, *font, 50), true));
		}
	}


	float _posX = (_windowSize.x - 500.0f) / 2;
	float _sizeY = 50.0f;
	float _posY = (_windowSize.y - _sizeY * texts.size()) / 2;
	Vector2f _pos = Vector2f(_posX, _posY);
	int _i = 0;
	for (TextData* _text : texts) {
		_text->onClick.push_back(_functions[_i]);
		_text->text->setPosition(_pos);
		_pos.y += 100;
		_i++;
	}

	currentText = texts[0];
	currentText->text->setFillColor(Color::Red);

	maxIndex = _names.size();

}

void MenuOption::HandleGamepadClick(Event _event)
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
			else if (_ydirectionFle == 0) canClick = false;
		}
	}
	if (_event.type == Event::JoystickButtonPressed) {

		if (_event.joystickButton.button == 0) {
			currentText->onClick[0]();
		}

	}
	
}

void MenuOption::MoveUp()
{
	index++;
	if (index >= maxIndex) index--;
	currentText->text->setFillColor(sf::Color::White);
	currentText = texts[index];
	currentText->text->setFillColor(sf::Color::Red);
	canClick = false;

}

void MenuOption::MoveDown()
{
	index--;
	if (index < minIndex) index++;
	currentText->text->setFillColor(sf::Color::White);
	currentText = texts[index];
	currentText->text->setFillColor(sf::Color::Red);
	canClick = false;
}

void MenuOption::HandleEvents(RenderWindow& _window)
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

void MenuOption::ChangeVolume()
{

}

bool MenuOption::Show()
{

	RenderWindow& _window = Game::GetInstance().GetWindow();

	if (!inGame) {
		minIndex = 1;
		index = 1;
		currentText = texts[minIndex];
		currentText->text->setFillColor(Color::Red);
	}
	else if (inGame) {
		minIndex = 0;
		index = 0;
		for (TextData* _text : texts) {
			_text->text->setFillColor(Color::White);
		}
		currentText = texts[minIndex];
		currentText->text->setFillColor(Color::Red);
	}

	while (_window.isOpen())
	{
		HandleEvents(_window);

		const View _view(FloatRect(Vector2f(0.0f, 0.0f), Vector2f(1920.0f, 1080.0f)));
		_window.setView(_view);
		_window.clear();
		_window.draw(*background);
		if (inGame) {
			for (TextData* _text : texts) {
				_window.draw(*_text->text);
			}
		}
		else{
			for (TextData* _text : texts) {
				if (_text->inGame) continue;
				_window.draw(*_text->text);
			}
		}
		

		_window.display();
	}
	return true;
}