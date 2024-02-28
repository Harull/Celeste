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
	Character() = default;
	Character(const sf::Vector2f _size, const sf::Vector2f _position, const bool _isVisible = false);

	void SetShape(const Vector2f& _size)
	{
		shape->setScale(_size);
	}


private:
	void InitShape();

public:
	bool MovingLeftRight(const sf::Event& _event);
	bool Jump(const sf::Event& _event);
	virtual void Update();
	void Move();
	void Dash();


};

