#include "LevelSelectorMenu.h"
#include "Game.h"
#include "TextureManager.h"
#include "FontManager.h"
#include "Macro.h"
#include "TimerManager.h"

LevelSelectorMenu::LevelSelectorMenu()
{
    levelButtons = vector<Text*>();
    background = nullptr;
	backgroundPath = vector<string>();
    font = nullptr;
    timer = nullptr;
	currentLevel = 1;
    currentAlpha = 255.0f;
    alphaFactor = 3.f;
	canClick = true;
    
}

LevelSelectorMenu::~LevelSelectorMenu()
{
    for (auto _button : levelButtons) {
		delete _button;
    }
    delete background;
    if (timer) timer->SetToRemove(true);

}

void LevelSelectorMenu::Init(const int _levelCounts)
{
    Vector2u _windowSize = Game::GetInstance().GetWindowSize();


    for (int _i = 0; _i < _levelCounts; ++_i)
    {
        backgroundPath.push_back("Assets/Background/game_selector_background" + std::to_string(_i + 1) + ".png");
    }

	background = new RectangleShape(Vector2f(1920.0f, 1080.0f));
    TextureManager::GetInstance().Load(background, backgroundPath[0]);
    font = new Font();
    if (!font->loadFromFile("Assets/Fonts/Renogare.otf"))
    {
        cerr << "ERROR - Font non charge" << endl;
    }

	Vector2f _startPosition = Vector2f(100, 400);
    for (int _i = 1; _i < _levelCounts + 1; _i++)
    {
        levelButtons.push_back(new Text("Level "+to_string(_i), *font, 50));

    }

    for (Text* _button : levelButtons)
    {
		_button->setPosition(_startPosition);
		_startPosition.y += 100;
    }

}

void LevelSelectorMenu::HandleMouseClick(Mouse::Button _button, const Vector2i& _mousePosition, RenderWindow& _window)
{
	if (!canClick) return;
    if (_button == Mouse::Left)
    {

        if (levelButtons[0]->getGlobalBounds().contains((float)_mousePosition.x, (float)_mousePosition.y))
        {
            nextPath = backgroundPath[0];
            TransitionFill();
            currentLevel = 1;
        }
        else if (levelButtons[1]->getGlobalBounds().contains((float)_mousePosition.x, (float)_mousePosition.y))
        {
            nextPath = backgroundPath[1];
            TransitionFill();
            currentLevel = 2;

        }
        else if (levelButtons[2]->getGlobalBounds().contains((float)_mousePosition.x, (float)_mousePosition.y))
        {
            nextPath = backgroundPath[2];
            TransitionFill();
            currentLevel = 3;

        }

    }
}

void LevelSelectorMenu::HandleKeyboardClick(Keyboard::Scancode _button) {
    if (!canClick) return;
    if (_button == sf::Keyboard::C) {
		Game::GetInstance().SelectLevel(currentLevel);
    }
    if (_button == sf::Keyboard::X) {
       
		FirstMenu::GetInstance().Show();
    }
}

void LevelSelectorMenu::HandleEvents(RenderWindow& _window)
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
        else if (_event.type == Event::KeyPressed)
        {
            HandleKeyboardClick(_event.key.scancode);
        }
    }
}

bool LevelSelectorMenu::Show()
{
    RenderWindow& _window = Game::GetInstance().GetWindow();
    while (_window.isOpen())
    {
        TimerManager::GetInstance().Update();
        HandleEvents(_window);

        const View _view(FloatRect(Vector2f(0.0f, 0.0f), Vector2f(1920.0f, 1080.0f)));
        _window.setView(_view);
        _window.clear();
        _window.draw(*background);
        for (Text* _button : levelButtons) {
			_window.draw(*_button);
        }
        _window.display();
    }
	return true;
}

void LevelSelectorMenu::TransitionFill() {
    canClick = false;
    const std::function<void()>& _callback = [&]() {

        Fade(background, (unsigned int)currentAlpha);
        MultiFade(levelButtons, (unsigned int)currentAlpha);

        currentAlpha -= alphaFactor;
        if (currentAlpha <= 0 || currentAlpha >= 255)
        {
            timer->Pause();
            timer->Reset();
            TextureManager::GetInstance().Load(background, nextPath);
            TransitionUnFill();

        }};
    timer = new Timer("FadeTimer", _callback, sf::seconds(0.01f), true, true);
}



void LevelSelectorMenu::TransitionUnFill()
{
    const std::function<void()>& _callback2 = [&]() {
        Fade(background, (unsigned int)currentAlpha);
        MultiFade(levelButtons, (unsigned int)currentAlpha);

        currentAlpha += alphaFactor;
        if (currentAlpha <= 0 || currentAlpha >= 255)
        {
            timer->Pause();
            timer->Reset();
            canClick = true;
        }};
    timer = new Timer("FadeTimer2", _callback2, sf::seconds(0.01f), true, true);
}