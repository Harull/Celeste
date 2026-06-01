#pragma once
#include <SFML/Graphics.hpp>
#include "AnimationComponent.h"

using namespace sf;

class OtherWindow
{
	sf::RenderWindow secondWindow;
	sf::Texture texture;
	sf::Sprite* sprite;
	

public:
	OtherWindow();
	~OtherWindow();

public:
	void Run();


};

