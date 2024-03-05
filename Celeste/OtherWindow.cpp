#include "OtherWindow.h"
#include "TextureManager.h"
#include "Game.h"

OtherWindow::OtherWindow()
{
    sprite = new Sprite();
}

OtherWindow::~OtherWindow()
{
    delete sprite;
}

void OtherWindow::Run()
{
    sf::RenderWindow& _mainWindow = Game::GetInstance().GetWindow();
    _mainWindow.setActive(false);
    _mainWindow.setVisible(false);
    secondWindow.create(sf::VideoMode(800, 600), "Other Window");
    secondWindow.setActive();
    secondWindow.requestFocus();
    TextureManager::GetInstance().Load(sprite, "Assets/IMG_5286.jpg", false, true);
    
    while (secondWindow.isOpen())
    {
        sf::Event event;
        while (secondWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                secondWindow.close();
        }
        
        sf::Vector2u windowSize = secondWindow.getSize();
        sprite->setScale(static_cast<float>(windowSize.x) / sprite->getTexture()->getSize().x,
            static_cast<float>(windowSize.y) / sprite->getTexture()->getSize().y);

        secondWindow.clear();
        secondWindow.draw(*sprite);
        secondWindow.display();
    }
    _mainWindow.setActive(true);
    _mainWindow.setVisible(true);

}


