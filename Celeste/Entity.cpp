#include "Entity.h"
#include "EntityManager.h"
#include "TextureManager.h"
#include "TimerManager.h"
#include "Component.h"


Entity::Entity(const EntityData& _data, std::vector<Component*> _components)
	: IManageable(_data.name) 
{
	shape = new sf::RectangleShape(_data.size);
	shape->setFillColor(Color::White);
	shape->setPosition(_data.position);
	originalPosition = _data.position;
	components = _components;
	type = _data.type;
	if (_data.path != "") {
		TextureManager::GetInstance().Load(shape, _data.path);
	}
	collisionReaction = nullptr;
	Register();

}

Entity::~Entity()
{
	delete shape;
	shape = nullptr;
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
	for (Component* _component : components)
	{
		_component->Update();
	}
}

void Entity::Reset()
{
}
