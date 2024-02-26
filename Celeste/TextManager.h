#pragma once
#include "TextData.h"
#include "IManager.h"
#include "Singleton.h"


class TextManager : public Singleton<TextManager>, public IManager<string, TextData>
{

public:
	static void Print(const string& _id, const std::string& _text, const vector<GameState>& _whenDisplayed, const sf::Vector2f& _position = { 0,0 },
		const unsigned int _characterSize = 16, const std::string& _fontPath = "")
	{
		TextData* _newText = new TextData(_id, _text, _position, _characterSize, _whenDisplayed, _fontPath);
	}

public:
	void DisplayAllTexts();
	void CloseAll();
	bool Contains(const string& _id, const string& _value);

};

