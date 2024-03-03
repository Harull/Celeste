#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Menu.h"

using namespace sf;
using namespace std;

class LevelSelectorMenu : public Menu, public Singleton<LevelSelectorMenu>
{
private:
	vector<Text*> levelButtons;
    float currentAlpha;
    float alphaFactor;
    bool canClick;
    Timer* timer;
    Shape* background;
    vector<string> backgroundPath;
    Font* font;
	string nextPath;
	int currentLevel;




    void HandleMouseClick(Mouse::Button _button, const Vector2i& _mousePosition, RenderWindow& _window);
    void HandleKeyboardClick(Keyboard::Scancode _button);
    void HandleEvents(RenderWindow& _window);

    void TransitionFill();
    void TransitionUnFill();

public:

    LevelSelectorMenu();
    ~LevelSelectorMenu();


    void Init(const int _levelCounts);
    virtual bool Show() override;

};