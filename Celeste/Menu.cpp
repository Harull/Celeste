// Menu.cpp
#include "Menu.h"
#include "Timer.h"
#include "TimerManager.h"
#include "TextureManager.h"
#include "Macro.h"

Menu::Menu()
{
	currentAlpha = 255.0f;
	alphaFactor = 3.f;
	canClick = true;
	backgroundShape = nullptr;
	timer = nullptr;
}

Menu::~Menu() {
	delete backgroundShape;
	delete nextShape;
	if (timer) timer->SetToRemove(true);  

}


void Menu::ShowMenu(sf::RenderWindow& window)
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
		static_cast<float>(window.getSize().x) / _backgroundSprite.getLocalBounds().width,
		static_cast<float>(window.getSize().y) / _backgroundSprite.getLocalBounds().height
	);

	sf::Text _play("Climb", _font, 80);
	sf::Text _options("Options", _font, 50);
	sf::Text _exit("Exit", _font, 50);

	_play.setPosition(180, 400);
	_options.setPosition(180, 510);
	_exit.setPosition(180, 575);

	while (window.isOpen())
	{
		sf::Event _event;
		while (window.pollEvent(_event))
		{
			if (_event.type == sf::Event::Closed) window.close();
			if (_event.type == sf::Event::MouseButtonPressed)
			{
				if (_event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2i _mousePosition = sf::Mouse::getPosition(window);
					if (_play.getGlobalBounds().contains(_mousePosition.x, _mousePosition.y))
					{
						window.clear();
						return;
					}
					else if (_options.getGlobalBounds().contains(_mousePosition.x, _mousePosition.y))
					{

					}
					else if (_exit.getGlobalBounds().contains(_mousePosition.x, _mousePosition.y))
					{
						window.close();
					}
				}
			}
		}

		window.clear();
		window.draw(_backgroundSprite);
		window.draw(_play);
		window.draw(_options);
		window.draw(_exit);
		window.display();

	}
}

void Menu::ShowLevelSelector(sf::RenderWindow& window)
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


	sf::Text _level1("Level 1", _font, 80);
	sf::Text _level2("Level 2", _font, 80);
	sf::Text _level3("Level 3", _font, 80);
	sf::Text _exit("Retour", _font, 50);

	_level1.setPosition(0, 400);
	_level2.setPosition(0, 500);
	_level3.setPosition(0, 600);
	_exit.setPosition(0, 0);

	while (window.isOpen())
	{
		TimerManager::GetInstance().Update();

		sf::Event _event;
		while (window.pollEvent(_event))
		{
			
			if (_event.type == sf::Event::Closed)
				window.close();
			if (canClick) {
				if (_event.type == sf::Event::MouseButtonPressed)
				{
					if (_event.mouseButton.button == sf::Mouse::Left)
					{
						sf::Vector2i _mousePosition = sf::Mouse::getPosition(window);

						if (_level1.getGlobalBounds().contains(_mousePosition.x, _mousePosition.y))
						{
							nextPath = _backgroundTextures[0];
							TransitionFill();
						}
						else if (_level2.getGlobalBounds().contains(_mousePosition.x, _mousePosition.y))
						{
							nextPath = _backgroundTextures[1];
							TransitionFill();

						}
						else if (_level3.getGlobalBounds().contains(_mousePosition.x, _mousePosition.y))
						{
							nextPath = _backgroundTextures[2];
							TransitionFill();

						}
						if (_exit.getGlobalBounds().contains(_mousePosition.x, _mousePosition.y))
						{
							window.close();
						}
					}
				}
			}
		}

		window.clear();
		window.draw(*backgroundShape);
		window.draw(_level1);
		window.draw(_level2);
		window.draw(_level3);
		window.draw(_exit);
		window.display();
	}
}


void Menu::TransitionFill() {
	canClick = false;
	const std::function<void()>& _callback = [&]() {
		Fade(backgroundShape, currentAlpha);

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

		currentAlpha += alphaFactor;
		if (currentAlpha <= 0 || currentAlpha >= 255)
		{
			timer->Pause();
			timer->Reset();
			canClick = true;
		}};
	timer = new Timer("FadeTimer2", _callback2, sf::seconds(0.01f), true, true);
}
