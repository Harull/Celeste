#pragma once
#include<SFML/Graphics.hpp>
#include "Entity.h"
#include "Component.h"
#include "CollisionComponent.h"
#include"AnimationComponent.h"
#include <vector>
#include"Macro.h"
using namespace sf;

class MovementComponent : public Component
{
    float velocity;
    Vector2f direction;
    bool canMove;
    

public:
    bool GetCanMove()const
    {
        return canMove;
    }
    Vector2f GetDirection()const
    {
        return direction;
    }
    float GetVelocity()const
    {
        return velocity;
    }
    void SetCanMove(const bool _status)
    {
        canMove = _status;
    }
    void SetDirection(const Vector2f& _direction)
    {
        direction = _direction;
    }
    void UpdateVelocity(const float _update)
    {
        velocity += _update;
    }
    bool IsAtLocation(Vector2f _destination) const
    {
        return Distance(owner->GetPosition(), _destination) <= 10.0f;
    }
public:
    MovementComponent(Entity* _owner,bool _canMove=true);
    MovementComponent(Entity* _owner, const float _velocity, const Vector2f& _direction, const bool _canMove = true);

public:
    void Update()override;
    void Move(const sf::Vector2f& _direction = sf::Vector2f());
    bool TryToMove(Entity* _entity, const Vector2f& _direction);
    Vector2f GetDirectionByPositions(Vector2f _destination);
    void UpdateAnimations();
    

};