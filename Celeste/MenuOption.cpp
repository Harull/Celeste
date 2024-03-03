#include "MenuOption.h"
#include "Game.h"
#include "TextureManager.h"
#include "FontManager.h"
#include "LevelSelectorMenu.h"

MenuOption::MenuOption()
{
	currentVolumeCount = 2;

	volume = new Text();
	back = new Text();
	backLevelSelect = new Text();
	decreaseVolume = new Text();
	increaseVolume = new Text();
	currentVolume = new Text();

	background = new Sprite();
	font = new Font();

	inGame = false;

}

MenuOption::~MenuOption()
{
	delete volume;
	delete currentVolume;
	delete back;
	delete backLevelSelect;
	delete decreaseVolume;
	delete increaseVolume;

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

	currentVolume->setString(to_string(currentVolumeCount));
	volume->setString("Volume");
	back->setString("Resume");
	backLevelSelect->setString("Retour");
	decreaseVolume->setString("<");
	increaseVolume->setString(">");

	if (!font->loadFromFile("Assets/Fonts/Renogare.otf"))
	{
		cerr << "ERROR - Font non charge" << endl;
	}

	volume->setFont(*font);
	currentVolume->setFont(*font);
	back->setFont(*font);
	backLevelSelect->setFont(*font);
	decreaseVolume->setFont(*font);
	increaseVolume->setFont(*font);



	volume->setCharacterSize(50);
	currentVolume->setCharacterSize(50);
	back->setCharacterSize(50);
	backLevelSelect->setCharacterSize(50);
	decreaseVolume->setCharacterSize(50);
	increaseVolume->setCharacterSize(50);

	volume->setPosition(700, 575);
	decreaseVolume->setPosition(925, 575);
	currentVolume->setPosition(950, 575);
	increaseVolume->setPosition(1025, 575);

	back->setPosition(180, 510);
	backLevelSelect->setPosition(180, 575);


}

void MenuOption::HandleMouseClick(Mouse::Button _button, const Vector2i& _mousePosition, RenderWindow& _window)
{
	if (_button == Mouse::Left)
	{

		if (back->getGlobalBounds().contains(static_cast<float>(_mousePosition.x), static_cast<float>(_mousePosition.y)))
		{
			Game::GetInstance().Resume();
		}
		else if (backLevelSelect->getGlobalBounds().contains(static_cast<float>(_mousePosition.x), static_cast<float>(_mousePosition.y)))
		{
			MenuOption::GetInstance().SetInGame(false);
			LevelSelectorMenu::GetInstance().Show();
		}
		else if (decreaseVolume->getGlobalBounds().contains(static_cast<float>(_mousePosition.x), static_cast<float>(_mousePosition.y)))
		{
			currentVolumeCount--;
			if (currentVolumeCount < 0) {
				currentVolumeCount = 0;
				return;
			}
			currentVolume->setString(to_string(currentVolumeCount));
			MusicManager::GetInstance().DecreaseVolume();
		}
		else if (increaseVolume->getGlobalBounds().contains(static_cast<float>(_mousePosition.x), static_cast<float>(_mousePosition.y)))
		{
			currentVolumeCount++;
			if (currentVolumeCount > 10) {
				currentVolumeCount = 10;
				return;
			}
			currentVolume->setString(to_string(currentVolumeCount));
			MusicManager::GetInstance().IncreaseVolume();
		}
	}
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
		else if (_event.type == Event::MouseButtonPressed)
		{
			HandleMouseClick(_event.mouseButton.button, Mouse::getPosition(_window), _window);
		}
	}
}

bool MenuOption::Show()
{

	RenderWindow& _window = Game::GetInstance().GetWindow();

	while (_window.isOpen())
	{
		HandleEvents(_window);

		const View _view(FloatRect(Vector2f(0.0f, 0.0f), Vector2f(1920.0f, 1080.0f)));
		_window.setView(_view);

		_window.clear();
		_window.draw(*background);
		_window.draw(*volume);
		_window.draw(*decreaseVolume);
		_window.draw(*currentVolume);
		_window.draw(*increaseVolume);
		_window.draw(*backLevelSelect);
		if (inGame) {
			_window.draw(*back);
		}

		_window.display();
	}
	return true;
}