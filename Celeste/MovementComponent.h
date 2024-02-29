#pragma once
#include<SFML/Graphics.hpp>
#include "Entity.h"
#include "Component.h"
#include "CollisionComponent.h"
#include"AnimationComponent.h"
#include <vector>

using namespace sf;

class MovementComponent : public Component
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
        UpdateAnimations();
        
    }
    void UpdateVelocity(const float _update)
    {
        velocity += _update;
    }

public:
    MovementComponent(Entity* _owner);
    MovementComponent(Entity* _owner, const float _velocity, const Vector2f& _direction, const bool _canMove = true);

private:
    void UpdateAnimations();

public:
    void Update()override;
    void Move();
    bool TryToMove(Entity* _entity, const Vector2f& _direction);

};