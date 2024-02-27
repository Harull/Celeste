#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"

class Component;

class Character : public Entity
{
	bool isVisible;

public:
	Character() = default;
	Character(const sf::Vector2f _size, const sf::Vector2f _position, const bool _isVisible = false);

private:
	void InitShape();

public:
	bool MovingLeftRight(const sf::Event& _event);
	void Dash();


};

