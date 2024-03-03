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

	Text* volume;
	Text* currentVolume;
    Text* back;
    Text* backLevelSelect;
	Text* decreaseVolume;
	Text* increaseVolume;
	bool inGame;


    Sprite* background;
    Font* font;



    void HandleMouseClick(Mouse::Button _button, const Vector2i& _mousePosition, RenderWindow& _window);
    void HandleEvents(RenderWindow& _window);

public:


    MenuOption();
    ~MenuOption();

    void SetInGame(const bool _value) {
        inGame = _value;
    }

    void Init();
    virtual bool Show() override;

};