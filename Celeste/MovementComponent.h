#pragma once
#include<SFML/Graphics.hpp>
#include "Entity.h"
#include "CollisionComponent.h"
#include<vector>

using namespace sf;

class MovementComponent
{
    float velocity;
    Vector2f direction;
    bool canMove;

public:
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

public:
    MovementComponent();
    MovementComponent(const float _velocity, const Vector2f _direction, const bool _canMove = true);

public:
    void Move(CollisionComponent* _collision, Entity* _entity);
    bool TryToMove(CollisionComponent* _collision, Entity* _entity, const Vector2f& _direction);

};