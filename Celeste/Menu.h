// Menu.h
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class Menu
{

public:
    Menu();
    void ShowMenu(sf::RenderWindow& window);
    void ShowLevelSelector(sf::RenderWindow& window);
};
