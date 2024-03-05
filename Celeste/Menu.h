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
	bool canChangeValue;
	function<void()> onClick;
	

	TextData() = default;
	TextData(string _name, Text* _text, const bool _inGame, const bool _canChangeValue = false) 
		: name(_name), text(_text), inGame(_inGame), canChangeValue(_canChangeValue){}

	~TextData() {
		delete text;
	}
};

class Menu
{


public:

	 virtual bool Show() = 0;
};
