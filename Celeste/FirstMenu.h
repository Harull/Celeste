#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Menu.h"
#include "Singleton.h"

using namespace sf;
using namespace std;

struct TextData {
    string name;
	Text* text;

    TextData() = default;
	TextData(string _name, Text* _text) : name(_name), text(_text) {}

    ~TextData() {
		delete text;
    }
};

class FirstMenu : public Menu, public Singleton<FirstMenu>
{
private:
    vector<TextData*> texts;

    Sprite* background;
    Font* font;

    int index;
	int maxIndex;




    void HandleMouseClick(Mouse::Button _button, const Vector2i& _mousePosition, RenderWindow& _window);
    void HandleKeyboardClick(Event _event);
    void HandleEvents(RenderWindow& _window);

public:

    FirstMenu();
    ~FirstMenu();

    void Init();
    virtual bool Show() override;

};