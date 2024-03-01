// Menu.cpp
#include "Menu.h"

Menu::Menu()
{
}


void Menu::ShowMenu(sf::RenderWindow& window)
{
    sf::Font _font;
    if (!_font.loadFromFile("Assets/Fonts/Renogare.otf")) {
        cout << "ERROR - Font non chargé" << endl;
    }

    sf::Texture _backgroundTexture;
    if (!_backgroundTexture.loadFromFile("Assets/Background/celeste_background.png")) {
        std::cout << "ERROR - Texture du fond d'écran non chargée" << std::endl;
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
    _exit.setPosition(180, 580);

    while (window.isOpen())
    {
        sf::Event _event;
        while (window.pollEvent(_event))
        {
            if (_event.type == sf::Event::Closed)
                window.close();

            if (_event.type == sf::Event::MouseButtonPressed)
            {
                if (_event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i _mousePosition(sf::Mouse::getPosition(window));
                    if (_play.getGlobalBounds().contains(_mousePosition.x, _mousePosition.y))
                    {
                        window.clear();
                        return;
                    }
                    else if (_options.getGlobalBounds().contains(_mousePosition.x, _mousePosition.y))
                    {
						ShowOptions(window);
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
        cout << "ERROR - Font non charg�" << endl;
    }

    sf::Texture _backgroundTextures[3];
    for (int _i = 0; _i < 3; ++_i)
    {
        if (!_backgroundTextures[_i].loadFromFile("Assets/Background/game_selector_background" + std::to_string(_i + 1) + ".png"))
        {
            std::cout << "ERROR - Texture du fond d'�cran level " << _i + 1 << " non charg�e" << std::endl;
        }
    }

    sf::Sprite _backgroundSprite(_backgroundTextures[0]);
    _backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / _backgroundSprite.getLocalBounds().width,
        static_cast<float>(window.getSize().y) / _backgroundSprite.getLocalBounds().height
    );

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
        sf::Event _event;
        while (window.pollEvent(_event))
        {
            if (_event.type == sf::Event::Closed)
                window.close();

            if (_event.type == sf::Event::MouseButtonPressed)
            {
                if (_event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i _mousePosition = sf::Mouse::getPosition(window);

                    if (_level1.getGlobalBounds().contains(_mousePosition.x, _mousePosition.y))
                    {
                        _backgroundSprite.setTexture(_backgroundTextures[0]);
                        return;
                    }
                    else if (_level2.getGlobalBounds().contains(_mousePosition.x, _mousePosition.y))
                    {
                        _backgroundSprite.setTexture(_backgroundTextures[1]);
                    }
                    else if (_level3.getGlobalBounds().contains(_mousePosition.x, _mousePosition.y))
                    {
                        _backgroundSprite.setTexture(_backgroundTextures[2]);
                    }
					if (_exit.getGlobalBounds().contains(_mousePosition.x, _mousePosition.y))
					{
						window.close();
					}
				}
            }
        }

        window.clear();
        window.draw(_backgroundSprite);
        window.draw(_level1);
        window.draw(_level2);
        window.draw(_level3);
        window.draw(_exit);
        window.display();
    }
}

void Menu::ShowOptions(sf::RenderWindow& window)
{

    sf::Font _font;
    if (!_font.loadFromFile("Assets/Fonts/Renogare.otf")) {
        cerr << "ERROR - Font not loaded" << endl;
        return;
    }

    sf::Texture _backgroundTexture;
    if (!_backgroundTexture.loadFromFile("Assets/Background/options_background.png")) {
        std::cout << "ERROR - Texture du fond d'écran non chargée" << std::endl;
    }

    sf::Sprite _backgroundSprite(_backgroundTexture);
    _backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / _backgroundSprite.getLocalBounds().width,
        static_cast<float>(window.getSize().y) / _backgroundSprite.getLocalBounds().height
    );

    sf::Text _title("Options", _font, 80);
    _title.setPosition(180, 100);

    sf::Text _musicVolumeLabel("Musique volume: ", _font, 50);
    _musicVolumeLabel.setPosition(700, 400);

    sf::Text _volumeLevel("10", _font, 50);
    _volumeLevel.setPosition(1200, 400);

    sf::Text _decreaseVolume("<", _font, 50);
    _decreaseVolume.setPosition(1160, 400);

    sf::Text _increaseVolume(">", _font, 50);
    _increaseVolume.setPosition(1275, 400);

    sf::Text _back("Back", _font, 50);
    _back.setPosition(1700, 950);

    while (window.isOpen())
    {
        sf::Event _event;
        while (window.pollEvent(_event))
        {
            if (_event.type == sf::Event::Closed)
                window.close();

            if (_event.type == sf::Event::MouseButtonPressed)
            {
                if (_event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i _mousePosition = sf::Mouse::getPosition(window);

                    if (_decreaseVolume.getGlobalBounds().contains(_mousePosition.x, _mousePosition.y))
                    {
                        int _currentVolume = std::stoi(_volumeLevel.getString().toAnsiString());
                        if (_currentVolume > 0)
                            _volumeLevel.setString(std::to_string(_currentVolume - 1));
                        MusicManager::GetInstance().DecreaseVolume();
                    }
                    else if (_increaseVolume.getGlobalBounds().contains(_mousePosition.x, _mousePosition.y))
                    {
                        int _currentVolume = std::stoi(_volumeLevel.getString().toAnsiString());
                        if (_currentVolume < 10)
                            _volumeLevel.setString(std::to_string(_currentVolume + 1));
                        MusicManager::GetInstance().IncreaseVolume(); 
                    }
                    else if (_back.getGlobalBounds().contains(_mousePosition.x, _mousePosition.y))
                    {
                        return;
                    }
                }
            }
        }

        window.clear();
        window.draw(_backgroundSprite);
        window.draw(_title);
        window.draw(_back);
        window.draw(_musicVolumeLabel);
        window.draw(_decreaseVolume);
        window.draw(_volumeLevel);
        window.draw(_increaseVolume);
        window.display();
    }
}
