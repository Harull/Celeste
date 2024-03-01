// Menu.h
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "MusicManager.h"
#include "TextureManager.h"


using namespace std;

class Menu
{
	MusicManager* musicManager;
public:
    Menu();

public:
    void ShowMenu(sf::RenderWindow& window);
    void ShowLevelSelector(sf::RenderWindow& window);
	void ShowOptions(sf::RenderWindow& window);
};
