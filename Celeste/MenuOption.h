#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Menu.h"
#include "Singleton.h"

using namespace sf;
using namespace std;

class MenuOption : public Menu, public Singleton<MenuOption>
{
private:
    int currentVolumeCount;

    vector<TextData*> texts;
    TextData* currentText;

    int index;
    int maxIndex;
	int minIndex;

    bool canClick;
	bool inGame;

    Sprite* background;
    Font* font;



    void HandleGamepadClick(Event _event);
    void HandleEvents(RenderWindow& _window);
	void ChangeVolume();

    void MoveDown();
    void MoveUp();

public:


    MenuOption();
    ~MenuOption();

    vector<TextData*> GetTexts() {
		return texts;
    }

    void SetInGame(const bool _value) {
        inGame = _value;
    }

    void Init();
    virtual bool Show() override;

};