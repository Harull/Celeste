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

    Sprite* background;
    Font* font;
    

    int index;
	int maxIndex;

	bool canClick;





    void HandleGamepadClick(Event _event);
    void HandleEvents(RenderWindow& _window);

	void MoveDown();
	void MoveUp();

public:

    FirstMenu();
    ~FirstMenu();

    void Init();
    virtual bool Show() override;

};
