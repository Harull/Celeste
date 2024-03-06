#include "MenuSoundBoard.h"
#include "Game.h"
#include "TextureManager.h"
#include "FontManager.h"
#include "Macro.h"
#include "SoundManager.h"
#include "MenuOption.h"

#define DEAD_ZONE 50.0f

#define PATH(name) "Assets/Songs/SoundBoard/" + string(name) + ".mp3"



MenuSoundBoard::MenuSoundBoard()
{
	background = nullptr;
	font = nullptr;
	positions = vector<Vector2f>();
	backgroundShape = nullptr;
	maxValue = 11;
	size = 0;
	halfSize = maxValue / 2;
	beginIndexToShow = 0;
	endIndexToShow = maxValue;
	halfSizeToShow = 0;
	halfSizeToShow2 = 0;
	index = halfSize;
	canClick = true;

	texts = vector<TextData*>();
	textsToShow = vector<TextData*>();
	currentText = nullptr;

}

MenuSoundBoard::~MenuSoundBoard()
{
	for (auto _text : texts) {
		delete _text;

	}delete font;
	delete backgroundShape;
	delete background;
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
	backgroundShape = new RectangleShape(Vector2f(500.0f, (_sizeY * maxValue) + 15.0f));
	backgroundShape->setPosition(_posX, _posY);
	backgroundShape->setFillColor(Color(0, 0, 0, 120));
	backgroundShape->setOutlineThickness(5.0f);

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


	for (string _name : _nameSongs) {
		texts.push_back(new TextData(_name,
			new Text(_name, *font, 50), false, true));
	}

	for (int _i = 0; _i < maxValue; _i++)
	{
		texts[_i]->text->setPosition(positions[_i]);
		textsToShow.push_back(texts[_i]);
	}
	size = static_cast<int>(texts.size());
	index = static_cast<int>(textsToShow.size()) / 2; 
	beginIndexToShow = 0;
	endIndexToShow = maxValue;
	currentText = textsToShow[index];
	currentText->text->setFillColor(Color::Red);
	halfSizeToShow2 = halfSizeToShow = static_cast<int>(textsToShow.size()) / 2;

}

void MenuSoundBoard::HandleGamepadClick(Event _event)
{
	float _axisYPositionJoy = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
	int _YDirectionJoy = (_axisYPositionJoy <= -DEAD_ZONE) ? -1 : _axisYPositionJoy >= DEAD_ZONE ? 1 : 0;

	float _axisypositionFle = sf::Joystick::getAxisPosition(0, sf::Joystick::PovY);
	int _ydirectionFle = (_axisypositionFle <= -DEAD_ZONE) ? -1 : _axisypositionFle >= DEAD_ZONE ? 1 : 0;

	if (_event.type == Event::JoystickMoved) {

		if (canClick) {
			if (_YDirectionJoy == 1) {
				MoveDown();

			}
			else if (_YDirectionJoy == -1) {

				MoveUp();
			}
		}
		else if (_YDirectionJoy == 0) canClick = true;
		if (canClick) {

			if (_ydirectionFle == -1) { //down
				MoveDown();

			}
			else if (_ydirectionFle == 1) { //up

				MoveUp();
			}
			else if (_event.joystickButton.button == 0) canClick = true;
		}
	}
	if (_event.type == Event::JoystickButtonPressed) {

		if (_event.joystickButton.button == 0) {
			SoundManager::GetInstance().Play(PATH(currentText->name));
		}
		if (_event.joystickButton.button == 1) {
			MenuOption::GetInstance().Show();
		}

	}
}

void MenuSoundBoard::MoveUp()
{
	if (beginIndexToShow == 0 || (endIndexToShow == size && index != halfSizeToShow2)) {
		index--;
		if (index < 0) index++;
		AllWhite();
		currentText = texts[index];
		currentText->text->setFillColor(Color::Red);
	}
	else {
		AllWhite();
		textsToShow.clear();
		beginIndexToShow--;
		endIndexToShow--;
		for (int _i = beginIndexToShow; _i < endIndexToShow; _i++)
		{
			textsToShow.push_back(texts[_i]);
		}
		textsToShow[halfSizeToShow]->text->setFillColor(Color::Red);

		for (int _i = 0; _i < maxValue; _i++)
		{
			textsToShow[_i]->text->setPosition(positions[_i]);
		}
		currentText = textsToShow[halfSizeToShow];
		halfSizeToShow2--;
		index--;
	}
	canClick = false;
}

void MenuSoundBoard::MoveDown()
{
	if (endIndexToShow == size || (beginIndexToShow == 0 && index != halfSizeToShow2)) {
		index++;
		if (index == size) index--;
		AllWhite();
		currentText = texts[index];
		currentText->text->setFillColor(Color::Red);
	}
	else {
		AllWhite();
		textsToShow.clear();
		beginIndexToShow++;
		endIndexToShow++;
		for (int _i = beginIndexToShow; _i < endIndexToShow; _i++)
		{
			textsToShow.push_back(texts[_i]);
		}
		textsToShow[halfSizeToShow]->text->setFillColor(Color::Red);

		for (int _i = 0; _i < maxValue; _i++)
		{
			textsToShow[_i]->text->setPosition(positions[_i]);
		}
		currentText = textsToShow[halfSizeToShow];
		halfSizeToShow2++;
		index++;
	}
	canClick = false;
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
		else if (_event.type == Event::JoystickButtonPressed || _event.type == Event::JoystickMoved)
		{
			HandleGamepadClick(_event);
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
		_window.draw(*backgroundShape);

		for (TextData* _text : textsToShow) {
			_window.draw(*_text->text);
		}

		_window.display();
	}
	return true;
}





