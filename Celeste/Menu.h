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



public:
    Menu();
    ~Menu();
    void ShowMenu(sf::RenderWindow& window);
    void ShowLevelSelector(sf::RenderWindow& window);
    void TransitionFill();
    void TransitionUnFill();
    void InitFadeTimer();
};
