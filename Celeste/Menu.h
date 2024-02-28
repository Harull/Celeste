// Menu.h
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"

using namespace std;

class Menu
{
    Game game;

public:
    Menu();
    void ShowMenu(sf::RenderWindow& window);
};
