#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"
#include"AnimationComponent.h"

class Component;

class Character : public Entity
{
	bool isVisible;
	AnimationComponent* animation;
	AnimationDirection direction;

public:
	Character();
	Character(const sf::Vector2f _size, const sf::Vector2f _position, const bool _isVisible = false);

private:
	void InitShape();
	void InitComponents();

public:
	virtual void Update();
	void Move();
	void Dash();


};

