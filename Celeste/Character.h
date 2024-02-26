#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"

class Component;

class Character : public Entity
{
	std::vector<Component*> components;
	bool isVisible;

public:
	Character(const sf::Vector2f _size, const sf::Vector2f _position, const bool _isVisible = false);

private:
	void InitShape();
	void InitComponents();

public:
	void Move();
	void Dash();


};

