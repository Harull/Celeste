#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Menu.h"

using namespace sf;
using namespace std;

class LevelSelectorMenu : public Menu, public Singleton<LevelSelectorMenu>
{
private:

	float currentAlpha;
	float alphaFactor;
	Timer* timer;
	Shape* background;
	vector<string> backgroundPath;
	Font* font;
	string nextPath;
	int currentLevel;


	TextData* currentText;
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

	LevelSelectorMenu();
	~LevelSelectorMenu();


	void Init(const int _levelCounts);
	virtual bool Show() override;

	};