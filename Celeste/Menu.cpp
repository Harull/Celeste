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

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("Assets/Background/celeste_background.png")) {
        std::cout << "ERROR - Texture du fond d'écran non chargée" << std::endl;
    }

    sf::Sprite backgroundSprite(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / backgroundSprite.getLocalBounds().width,
        static_cast<float>(window.getSize().y) / backgroundSprite.getLocalBounds().height
    );

    sf::Text _play("Climb", _font, 80);
    sf::Text _options("Options", _font, 50);
    sf::Text _exit("Exit", _font, 50);

    _play.setPosition(180, 400);
    _options.setPosition(180, 510);
    _exit.setPosition(180, 575);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                    if (_play.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                    {
                        window.clear();
                        return;
                    }
                    else if (_options.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                    {
    
                    }
                    else if (_exit.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                    {
                        window.close();  
                    }
                }
            }
        }

        window.clear();
        window.draw(backgroundSprite);
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
        cout << "ERROR - Font non chargé" << endl;
    }

    sf::Texture backgroundTextures[3];
    for (int i = 0; i < 3; ++i)
    {
        if (!backgroundTextures[i].loadFromFile("Assets/Background/game_selector_background" + std::to_string(i + 1) + ".png"))
        {
            std::cout << "ERROR - Texture du fond d'écran level " << i + 1 << " non chargée" << std::endl;
        }
    }

    sf::Sprite backgroundSprite(backgroundTextures[0]);
    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / backgroundSprite.getLocalBounds().width,
        static_cast<float>(window.getSize().y) / backgroundSprite.getLocalBounds().height
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
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                    if (_level1.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                    {
                        backgroundSprite.setTexture(backgroundTextures[0]);
                        return;
                    }
                    else if (_level2.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                    {
                        backgroundSprite.setTexture(backgroundTextures[1]);
                    }
                    else if (_level3.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                    {
                        backgroundSprite.setTexture(backgroundTextures[2]);
                    }
					if (_exit.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
					{
						window.close();
					}
				}
            }
        }

        window.clear();
        window.draw(backgroundSprite);
        window.draw(_level1);
        window.draw(_level2);
        window.draw(_level3);
        window.draw(_exit);
        window.display();
    }
}
