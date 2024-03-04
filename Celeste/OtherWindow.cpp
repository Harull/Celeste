#include "OtherWindow.h"
#include "TextureManager.h"

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
    secondWindow.create(sf::VideoMode(800, 600), "Other Window");

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
}


