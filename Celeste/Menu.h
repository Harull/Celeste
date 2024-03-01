// Menu.h
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Timer;

using namespace std;

class Menu
{
    float currentAlpha;
    float alphaFactor;
    bool canClick;
	sf::Shape* backgroundShape;
	sf::Shape* nextShape;
	Timer* timer;
    string nextPath;
	int currentLevel;
	vector<sf::Text*> levelTexts;





public:
    Menu();
    ~Menu();
    bool ShowMenu(sf::RenderWindow& window);
    int ShowLevelSelector(sf::RenderWindow& window);

    void TransitionFill();
    void TransitionUnFill();
};
