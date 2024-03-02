#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"
#include"AnimationComponent.h"

class Component;

class Character : public Entity
{
	// On aurait pu faire un jump component
	int maxYVelocity;
	int currentYVelocity;
	int currentJumpTimerIndex;

	bool isVisible;
	bool isJumping;

public:
	Character() = default;
	Character(const sf::Vector2f _size, const sf::Vector2f _position, const int _maxYVelocity, const bool _isVisible = false);

	void SetShape(const Vector2f& _size)
	{
		shape->setScale(_size);
	}
	void SetIsJumping(const bool _status)
	{
		isJumping = _status;
	}
	int GetCurrentJumpTimerIndex()const
	{
		return currentJumpTimerIndex;
	}
	bool GetIsJumping() const
	{
		return isJumping;
	}
	void SetPosition(const sf::Vector2f _position)
	{
		shape->setPosition(_position);
	}

private:
	void InitShape();

public:
	bool MovingLeftRight(const sf::Event& _event);
	bool Jump(const sf::Event& _event);
	void ResetJumpValues();
	virtual void Update();
	void Move();
	void Dash();

};

