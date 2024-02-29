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
                    sf::Vector2f mousePosition(sf::Mouse::getPosition(window));

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

