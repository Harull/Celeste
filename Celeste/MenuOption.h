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
    int currentVolumeCountMusic;
    int currentVolumeCount;

    vector<TextData*> texts;
    TextData* currentText;

    int index;
    int maxIndex;
	int minIndex;
    int offsetVolume;
    Snow* snow;
    Clock clock;
    float dt;

    bool canClick;
	bool canMoveJoystick;
	bool inGame;

    Sprite* background;
    Font* font;



    void HandleGamepadClick(Event _event);
    void HandleEvents(RenderWindow& _window);
	void ChangeVolumeMusic();
	void ChangeVolume();

    void MoveDown();
    void MoveUp();

    void Reset();


public:


    MenuOption();
    ~MenuOption();

    vector<TextData*> GetTexts() {
		return texts;
    }

    void SetInGame(const bool _value){
        inGame = _value;
    }

	bool IsInGame() const { return inGame; }

    void Init();
	void UpdateSnow();
    virtual bool Show() override;

};