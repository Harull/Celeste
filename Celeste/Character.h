#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"
#include"AnimationComponent.h"

class Component;
struct PortalData
{
	bool inPortal;
	
	float currentsize;

	PortalData()
	{
		
		inPortal = false;
		currentsize = 0;
	}
	
};
class Character : public Entity
{
	// J'avais fait un jump component mais je l'ai laissé à l'école donc rip
	int maxYVelocity;
	int currentYVelocity;
	int currentJumpTimerIndex;

	Vector2f checkPoint;
	
	bool isJumping;
	bool isClimbing;
	bool isDashing;
	bool isDie;

	int dashCount;
	int maxDashCount;

	int maxDashVelocity;
	int currentDashVelocity;
	int currentDashTimerIndex;

	sf::Vector2i dashDirectionBuffer;
	PortalData data;

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
	int GetCurrentDashTimerIndex()const
	{
		return currentDashTimerIndex;
	}
	bool GetIsJumping() const
	{
		return isJumping;
	}
	bool GetIsClimbing() const
	{
		return isClimbing;
	}
	bool GetIsDashing() const
	{
		return isDashing;
	}
	void SetCheckPoint(Vector2f _checkPoint)
	{
		checkPoint = _checkPoint;
	}
	Vector2f GetCheckPoint()
	{
		return checkPoint;
	}
	void SetDashCount(const int _dashCount)
	{
		dashCount = _dashCount;
	}
	int GetMaxDashCount()const
	{
		return maxDashCount;
	}
	void SetDie(bool _isDie)
	{
		isDie = _isDie;
	}
	bool IsDie()
	{
		return isDie;
	}
	bool GetHasDashes() const
	{
		return dashCount > 0;
	}
private:
	void InitShape();

public:
	bool MovingLeftRight(const sf::Event& _event);
	bool Jump(const sf::Event& _event);
	bool Dash(const sf::Event& _event);
	bool Climb(const sf::Event& _event);
	void ResetJumpValues();
	void ResetDashValues();
	virtual void Update();
	void SetPosition(const sf::Vector2f& newPosition);
	void Move();
	void Dash();
	void Die();
	void Respawn();

};

