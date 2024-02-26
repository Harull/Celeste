#pragma once
#include "IManageable.h"
#include <string>
#include <SFML/Graphics.hpp>
#include "Game.h"
using namespace std;

class TextData : public sf::Text, public IManageable<string>
{
	vector<GameState> whenDisplayed;

public:
	TextData() = default;
	TextData(const string& _id, const std::string& _text, const sf::Vector2f& _position,
		const unsigned int _characterSize, const vector<GameState>& _whenDisplayed, const std::string& _fontPath = "");

public:
	void UpdateString(const string& _text)
	{
		setString(_text);
	}

public:
	vector<GameState> GetWhenDisplayed() const
	{
		return whenDisplayed;
	}

private:
	void Register() override;
};


