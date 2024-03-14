#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Menu.h"
#include "Singleton.h"

using namespace sf;
using namespace std;



class FirstMenu : public Menu, public Singleton<FirstMenu>
{
private:
    vector<TextData*> texts;
	TextData* currentText;

	vector<Shape*> icons;

    Sprite* background;
    Font* font;
    Snow* snow;
    Clock clock;
    
    float dt;
    int index;
	int maxIndex;
    int hoveredIndex;

	bool canClick;

    void HandleGamepadClick(const Event _event);
    void HandleKeyboardClick(const Event _event);
    void HandleEvents(RenderWindow& _window);

	void MoveDown();
    void MoveUp();


public:

    FirstMenu();
    ~FirstMenu();

    void Init();

    virtual bool Show() override;

    void UpdateSnow();

};
