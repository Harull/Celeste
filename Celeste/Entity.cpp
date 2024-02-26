#include "Entity.h"
#include "EntityManager.h"
#include "TextureManager.h"
#include "TimerManager.h"
#include "Component.h"


Entity::Entity(const EntityData& _data)
	: IManageable(_data.name) 
{
	Register();
}

Entity::~Entity()
{
	for (Component* _component : components)
	{
		delete _component;
	}
}

void Entity::Register()
{
	EntityManager::GetInstance().Add(id, this);
}

void Entity::Update()
{
	const float _deltaTime = TimerManager::GetInstance().GetDeltaTime();
	for (Component* _component : components)
	{
		_component->Update(_deltaTime);
	}
}
