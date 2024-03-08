#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Menu.h"

using namespace sf;
using namespace std;

class MenuEndLevel : public Menu, public Singleton<MenuEndLevel>
{
private:


	TextData* text;
	float currentAlpha;
	float alphaFactor;
	Timer* timer;
	Timer* timer2;
	Timer* timerSound;
	vector<string> names;


	Font* font;
	string nextPath;
	int currentLevel;

	int index;
	int maxIndex;
	bool canClick;

	void HandleEvents(RenderWindow& _window);
	void HandleGamepadClick(Event _event);

	bool MoveRight();

	bool MoveLeft();

	void TransitionFill();
	void TransitionUnFill();


public:

	MenuEndLevel();
	~MenuEndLevel();


	void Init();
	virtual bool Show() override;

};