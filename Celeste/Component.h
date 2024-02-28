#pragma once
#include "Entity.h"

class Component
{
protected:
	Entity* owner;

public:
	Entity* GetOwner() 
	{ 
		return owner; 
	}

public:
	Component(Entity* _owner);

public:
	virtual void Update() {};
};
