#include "MenuOption.h"
#include "Game.h"
#include "TextureManager.h"
#include "FontManager.h"
#include "TimerManager.h"
#include "LevelSelectorMenu.h"
#include "MenuSoundBoard.h"
#include "Macro.h"
#include"EntityManager.h"
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

	offsetVolume = 0;

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
		"Volume",
		"SoundBoard",
		"Retour Menu",
	};

	vector<function<void()>> _functions =
	{
		[]() { Game::GetInstance().Resume(); } ,
		[this]() { ChangeVolume(); },
		[]() { MenuSoundBoard::GetInstance().Show(); } ,
		[]() {
			if (MenuOption::GetInstance().IsInGame()) {
				MenuOption::GetInstance().SetInGame(false);
				TimerManager::GetInstance().DeleteAll();
				LevelSelectorMenu::GetInstance().Show();
			}
			else {
				FirstMenu::GetInstance().Show();
			}
		}
	};

	for (string _name : _names) {
		if (_name != "Resume") {
			if (_name == "Volume") {
				texts.push_back(new TextData(_name,
					new Text(_name + "<" + to_string(currentVolumeCount) + ">", *font, 50), false, true));
			}
			else
			{
				texts.push_back(new TextData(_name, new Text(_name, *font, 50), false));
			}
		}
		else
		{
			texts.push_back(new TextData(_name, new Text(_name, *font, 50), true));
		}
	}


	float _posX = (_windowSize.x - 500.0f) / 2;
	float _sizeY = 50.0f;
	float _posY = (_windowSize.y - _sizeY * texts.size()) / 2;
	//float _posY = (_windowSize.y - 100 * texts.size() + texts.size() * texts[0]->text->getCharacterSize()) / 2;
	Vector2f _pos = Vector2f(_posX, _posY);
	int _i = 0;
	for (TextData* _text : texts) {
		_text->onClick = _functions[_i];
		_text->text->setPosition(_pos);
		_pos.y += 100;
		_i++;
	}

	currentText = texts[0];
	currentText->text->setFillColor(Color::Red);

	maxIndex = static_cast<int>(_names.size());

}

void MenuOption::HandleGamepadClick(Event _event)
{
	float _axisYPositionJoy = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
	int _yDirectionJoy = (_axisYPositionJoy <= -DEAD_ZONE) ? -1 : _axisYPositionJoy >= DEAD_ZONE ? 1 : 0;

	float _axisXPositionJoy = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
	int _xDirectionJoy = (_axisXPositionJoy <= -DEAD_ZONE) ? -1 : _axisXPositionJoy >= DEAD_ZONE ? 1 : 0;

	float _axisYPositionFle = sf::Joystick::getAxisPosition(0, sf::Joystick::PovY);
	int _yDirectionFle = (_axisYPositionFle <= -DEAD_ZONE) ? -1 : _axisYPositionFle >= DEAD_ZONE ? 1 : 0;

	float _axisXPositionFle = sf::Joystick::getAxisPosition(0, sf::Joystick::PovX);
	int _xDirectionFle = (_axisXPositionFle <= -DEAD_ZONE) ? -1 : _axisXPositionFle >= DEAD_ZONE ? 1 : 0;

	if (_event.type == Event::JoystickMoved) {

		if (canClick) {
			if (_yDirectionJoy == 1) {
				MoveUp();
			}
			else if (_yDirectionJoy == -1) {
				MoveDown();
			}
			if (canClick) {
				if (currentText->canChangeValue) {

					if (_xDirectionJoy == -1) {
						canClick = false;
						offsetVolume = _xDirectionJoy;
						currentText->onClick();
					}
					else if (_xDirectionJoy == 1) {
						canClick = false;
						offsetVolume = _xDirectionJoy;
						currentText->onClick();
					}
				}
			}
		}

		if (canClick) {
			if (_yDirectionFle == -1) {
				MoveUp();
			}
			else if (_yDirectionFle == 1) {
				MoveDown();
			}
		}

		if (currentText->canChangeValue) {
			if (canClick) {
				if (_xDirectionFle == -1) {
					canClick = false;
					offsetVolume = _xDirectionFle;
					currentText->onClick();
				}
				else if (_xDirectionFle == 1) {
					canClick = false;
					offsetVolume = _xDirectionFle;
					currentText->onClick();
				}
			}
		}
	}
	else if (_event.type == Event::JoystickButtonPressed) {
		if (currentText->canChangeValue) return;
		if (_event.joystickButton.button == 0) {
			currentText->onClick();
		}
	}

	if (_xDirectionFle == 0 && _yDirectionFle == 0 && _xDirectionJoy == 0 && _yDirectionJoy == 0) canClick = true;

}

void MenuOption::MoveUp()
{
	canClick = false;
	index++;
	if (index >= maxIndex) index--;
	currentText->text->setFillColor(sf::Color::White);
	currentText = texts[index];
	currentText->text->setFillColor(sf::Color::Red);

}



void MenuOption::MoveDown()
{
	canClick = false;
	index--;
	if (index < minIndex) index++;
	currentText->text->setFillColor(sf::Color::White);
	currentText = texts[index];
	currentText->text->setFillColor(sf::Color::Red);
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
	currentVolumeCount += offsetVolume;
	if (currentVolumeCount <= 0) {
		currentVolumeCount = 0;
		ModifyIntBetweenChevrons(currentVolumeCount, currentText->text);
		MusicManager::GetInstance().MuteVolume();
		return;
	}
	else if (currentVolumeCount > 10) {
		currentVolumeCount = 10;
		ModifyIntBetweenChevrons(currentVolumeCount, currentText->text);
		return;
	}

	if (offsetVolume == 0) return;
	else if (offsetVolume == 1) {
		MusicManager::GetInstance().IncreaseVolume();
		ModifyIntBetweenChevrons(currentVolumeCount, currentText->text);
	}
	else if (offsetVolume == -1) {
		MusicManager::GetInstance().DecreaseVolume();
		ModifyIntBetweenChevrons(currentVolumeCount, currentText->text);
	}
}

void MenuOption::Reset()
{
	if (!inGame) {
		minIndex = 1;
		index = 1;
		for (TextData* _text : texts) {
			_text->text->setFillColor(Color::White);
		}
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
}

bool MenuOption::Show()
{

	RenderWindow& _window = Game::GetInstance().GetWindow();

	Reset();

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
		else {
			for (TextData* _text : texts) {
				if (_text->inGame) continue;
				_window.draw(*_text->text);
			}
		}


		_window.display();
	}
	return true;
}