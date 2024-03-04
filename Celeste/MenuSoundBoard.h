#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Menu.h"

using namespace sf;
using namespace std;

class MenuSoundBoard : public Menu, public Singleton<MenuSoundBoard>
{
private:
    vector<Text*> buttons;
	Text* back;
	vector<string> paths;
	vector<Vector2f> positions;
    int index;
	int maxValue;
	Shape* forMouse;
    Shape* background;
    Font* font;
    string nextPath;






    void HandleMouseClick(Mouse::Button _button, const Vector2i& _mousePosition, RenderWindow& _window);
	void HandleMouseScroll(const float _delta, const Vector2i& _mousePosition, RenderWindow& _window);
    void HandleKeyboardClick(Keyboard::Scancode _button);
    void HandleEvents(RenderWindow& _window);


public:

    MenuSoundBoard();
    ~MenuSoundBoard();


    void Init();
    virtual bool Show() override;

};