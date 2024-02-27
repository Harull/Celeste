#pragma once
#include "Component.h"
#include "Entity.h"

class GravityComponent : public Component
{
	float gravity;


public:
	GravityComponent(Entity* _owner, const float _gravity);

public:
	void Update() override;
};

