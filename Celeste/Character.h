#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"
#include"AnimationComponent.h"

class Component;

class Character : public Entity
{
	// J'avais fait un jump component mais je l'ai laissé à l'école donc rip
	int maxYVelocity;
	int currentYVelocity;
	int currentJumpTimerIndex;
	Vector2f checkPoint;
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
	void SetCheckPoint(Vector2f _checkPoint)
	{
		checkPoint = _checkPoint;
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

