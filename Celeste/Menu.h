#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Timer.h"
#include "Singleton.h"


using namespace std;

struct TextData {
	string name;
	Text* text;
	bool inGame;

	TextData() = default;
	TextData(string _name, Text* _text, const bool _inGame) : name(_name), text(_text), inGame(_inGame){}
	vector<function<void()>> onClick;

	~TextData() {
		delete text;
	}
};

class Menu
{


public:

	 virtual bool Show() = 0;
};
