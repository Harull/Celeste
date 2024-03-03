#include "FirstMenu.h"
#include "Game.h"
#include "TextureManager.h"
#include "FontManager.h"
#include "LevelSelectorMenu.h"
#include "MenuOption.h"

FirstMenu::FirstMenu()
{
    play = new Text();
    options = new Text();
    exit = new Text();
    background = new Sprite();
	font = new Font();

}

FirstMenu::~FirstMenu()
{
    delete play;
    delete options;
    delete exit;
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

    play->setString("Climb");
    options->setString("Options");
    exit->setString("Exit");

    if (!font->loadFromFile("Assets/Fonts/Renogare.otf"))
    {
        cerr << "ERROR - Font non charge" << endl;
    }

    play->setFont(*font);
    options->setFont(*font);
    exit->setFont(*font);

    play->setCharacterSize(80);
    options->setCharacterSize(50);
    exit->setCharacterSize(50);

    play->setPosition(180, 400);
    options->setPosition(180, 510);
    exit->setPosition(180, 575);
}

void FirstMenu::HandleMouseClick(Mouse::Button _button, const Vector2i& _mousePosition, RenderWindow& _window)
{
    if (_button == Mouse::Left)
    {
        if (play->getGlobalBounds().contains(static_cast<float>(_mousePosition.x), static_cast<float>(_mousePosition.y)))
        {
            LevelSelectorMenu::GetInstance().Show();
        }
        else if (options->getGlobalBounds().contains(static_cast<float>(_mousePosition.x), static_cast<float>(_mousePosition.y)))
        {
			MenuOption::GetInstance().Show();
        }
        else if (exit->getGlobalBounds().contains(static_cast<float>(_mousePosition.x), static_cast<float>(_mousePosition.y)))
        {
            _window.close();
        }
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
        _window.draw(*play);
        _window.draw(*options);
        _window.draw(*exit);
        _window.display();
    }
    return true;
}