#pragma once
#include "Component.h"
#include "Entity.h"

class GravityComponent : public Component
{
	float gravity;


public:
	GravityComponent(Entity* _owner, const float _gravity);
public:
	float GetGravity() const
	{
		return gravity;
	}

public:
	void Update() override;
	void ApplyGravity(const bool _reverted = false);
};

