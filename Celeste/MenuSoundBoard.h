#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Menu.h"

using namespace sf;
using namespace std;

class MenuSoundBoard : public Menu, public Singleton<MenuSoundBoard>
{
private:

	vector<Vector2f> positions;
	Shape* backgroundShape;
    Shape* background;
    Font* font;

    int index;
	int maxValue;
    int halfSize;
	int halfSizeToShow;
	int halfSizeToShow2;
	int beginIndexToShow;
	int endIndexToShow;
	int size;
	vector<TextData*> texts;
	vector<TextData*> textsToShow;
    TextData* currentText;
	bool canClick;

    void HandleGamepadClick(Event _event);
    void HandleEvents(RenderWindow& _window);

    void AllWhite() {
		for (TextData* _text : textsToShow) {
			_text->text->setFillColor(Color::White);
		}
    }

	void MoveUp();
	void MoveDown();


public:

    MenuSoundBoard();
    ~MenuSoundBoard();


    void Init();
    virtual bool Show() override;

};
