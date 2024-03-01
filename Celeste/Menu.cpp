// Menu.cpp
#include "Menu.h"
#include "Timer.h"
#include "TimerManager.h"
#include "TextureManager.h"
#include "Macro.h"
#include "EventReactionManager.h"

Menu::Menu()
{
	currentAlpha = 255.0f;
	alphaFactor = 3.f;
	canClick = true;
	backgroundShape = nullptr;
	timer = nullptr;
	currentLevel = 1;
}

Menu::~Menu() {
	delete backgroundShape;
	delete nextShape;
	if (timer) timer->SetToRemove(true);  

}


bool Menu::ShowMenu(sf::RenderWindow& _window)
{
	sf::Font _font;
	if (!_font.loadFromFile("Assets/Fonts/Renogare.otf")) {
		cerr << "ERROR - Font non charge" << endl;
	}

	sf::Texture _backgroundTexture;
	if (!_backgroundTexture.loadFromFile("Assets/Background/celeste_background.png")) {
		std::cerr << "ERROR - Texture du fond d'ecran non chargee" << std::endl;
	}

	sf::Sprite _backgroundSprite(_backgroundTexture);
	_backgroundSprite.setScale(
		static_cast<float>(_window.getSize().x) / _backgroundSprite.getLocalBounds().width,
		static_cast<float>(_window.getSize().y) / _backgroundSprite.getLocalBounds().height
	);

	sf::Text _play("Climb", _font, 80);
	sf::Text _options("Options", _font, 50);
	sf::Text _exit("Exit", _font, 50);

	_play.setPosition(180, 400);
	_options.setPosition(180, 510);
	_exit.setPosition(180, 575);

	while (_window.isOpen())
	{
		sf::Event _event;
		while (_window.pollEvent(_event))
		{
			if (_event.type == sf::Event::Closed) _window.close();
			if (_event.type == sf::Event::MouseButtonPressed)
			{
				if (_event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2i _mousePosition = sf::Mouse::getPosition(_window);
					if (_play.getGlobalBounds().contains(_mousePosition.x, _mousePosition.y))
					{
						return true;
					}
					else if (_options.getGlobalBounds().contains(_mousePosition.x, _mousePosition.y))
					{

					}
					else if (_exit.getGlobalBounds().contains(_mousePosition.x, _mousePosition.y))
					{
						_window.close();
						return false;
					}
				}
			}
		}

		_window.clear();
		_window.draw(_backgroundSprite);
		_window.draw(_play);
		_window.draw(_options);
		_window.draw(_exit);
		_window.display();

	}
	return false;
}

int Menu::ShowLevelSelector(sf::RenderWindow& _window)
{
	sf::Font _font;
	if (!_font.loadFromFile("Assets/Fonts/Renogare.otf")) {
		cerr << "ERROR - Font non charg�" << endl;
	}

	vector<string> _backgroundTextures;
	for (int _i = 0; _i < 3; ++_i)
	{
		_backgroundTextures.push_back("Assets/Background/game_selector_background" + std::to_string(_i + 1) + ".png");
	}

	backgroundShape = new sf::RectangleShape(Vector2f(1920.0f, 1080.0f));
	nextShape = new sf::RectangleShape(Vector2f(1920.0f, 1080.0f));

	TextureManager::GetInstance().Load(backgroundShape, _backgroundTextures[0]);

	levelTexts.clear();
	levelTexts.push_back(new Text("Level 1", _font, 80));
	levelTexts.push_back(new Text("Level 2", _font, 80));
	levelTexts.push_back(new Text("Level 3", _font, 80));

	Vector2f _startPosition = Vector2f(0, 400);

	for (Text* _text : levelTexts)
	{
		_text->setPosition(_startPosition);
		_startPosition.y += 100;
	}

	while (_window.isOpen())
	{
		TimerManager::GetInstance().Update();

		sf::Event _event;
		while (_window.pollEvent(_event))
		{
			
			if (_event.type == sf::Event::Closed)
				_window.close();
			if (canClick) {
				if (_event.type == sf::Event::KeyPressed) {
					if (_event.key.code == sf::Keyboard::C) {
						return currentLevel;
					}
					if (_event.key.code == sf::Keyboard::X) {
						return -1;
						
					}
				}

				if (_event.type == sf::Event::MouseButtonPressed)
				{
					if (_event.mouseButton.button == sf::Mouse::Left)
					{

						sf::Vector2i _mousePosition = sf::Mouse::getPosition(_window);
						if (levelTexts[0]->getGlobalBounds().contains(_mousePosition.x, _mousePosition.y))
						{
							nextPath = _backgroundTextures[0];
							TransitionFill();
							currentLevel = 1;
						}
						else if (levelTexts[1]->getGlobalBounds().contains(_mousePosition.x, _mousePosition.y))
						{
							nextPath = _backgroundTextures[1];
							TransitionFill();
							currentLevel = 2;

						}
						else if (levelTexts[2]->getGlobalBounds().contains(_mousePosition.x, _mousePosition.y))
						{
							nextPath = _backgroundTextures[2];
							TransitionFill();
							currentLevel = 3;

						}
					}
				}
			}
		}

		_window.clear();
		_window.draw(*backgroundShape);
		for (Text* _text : levelTexts)
		{
			_window.draw(*_text);
		}
		_window.display();
	}
	return 0;
}

void Menu::TransitionFill() {
	canClick = false;
	const std::function<void()>& _callback = [&]() {

		Fade(backgroundShape, currentAlpha);
		MultiFade(levelTexts, currentAlpha);

		currentAlpha -= alphaFactor;
		if (currentAlpha <= 0 || currentAlpha >= 255)
		{
			timer->Pause();
			timer->Reset();
			TextureManager::GetInstance().Load(backgroundShape, nextPath);
			TransitionUnFill();
			
		}};
	timer = new Timer("FadeTimer", _callback, sf::seconds(0.01f), true, true);
}



void Menu::TransitionUnFill()
{
	const std::function<void()>& _callback2 = [&]() {
		Fade(backgroundShape, currentAlpha);
		MultiFade(levelTexts, currentAlpha);

		currentAlpha += alphaFactor;
		if (currentAlpha <= 0 || currentAlpha >= 255)
		{
			timer->Pause();
			timer->Reset();
			canClick = true;
		}};
	timer = new Timer("FadeTimer2", _callback2, sf::seconds(0.01f), true, true);
}
