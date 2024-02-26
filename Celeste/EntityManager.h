#pragma once

#include "Singleton.h"
#include "IManager.h"
#include "Entity.h"
#include "Game.h"

using namespace std;

//typedef int ID;

class EntityManager : public Singleton<EntityManager>, public IManager<string, Entity>
{

public:
	void Update();
	bool IsAvailable(const Vector2f& _position, const Vector2f& _size);
	void DisplayAllEntities() const;
};

