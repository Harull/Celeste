#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Dialog
{
    sf::RenderWindow window;
    sf::Font font;
    sf::Text text;
    std::string content;

    std::size_t currentCharIndex;
   
public:
        Dialog(std::string filename);

public:
        void Run();
        void loadContent();


};

