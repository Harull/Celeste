#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"

using namespace sf;
using namespace std;



class Object
{
protected:
	Shape* shape;
	Text* text;
	std::vector<GameState> whenDisplayed;

public:

	Shape* GetShape()
	{
		return shape;
	}

	Text* GetText()
	{
		return text;
	}

	Vector2f GetPosition() const
	{
		return shape->getPosition();
	}

	std::vector<GameState> GetWhenDisplayed()
	{
		return whenDisplayed;
	}

public:
	Object(const Vector2f& _size, const Vector2f& _position, const string& _path, const std::vector<GameState>& _whenDisplayed);
	Object(const float _size, const Vector2f& _position, const string& _path, const std::vector<GameState>& _whenDisplayed);
	Object(const int _textSize, const Vector2f& _position, const string& _path, const string& _text, const std::vector<GameState>& _whenDisplayed);
};

