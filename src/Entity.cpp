#include "Entity.h"
#include "EntityManager.h"
#include "TextureManager.h"
#include "TimerManager.h"
#include "Component.h"
#include "Game.h"
#include "Camera.h"
#include "Macro.h"

Entity::Entity(const EntityData& _data, const bool _isUpdatable, std::vector<Component*> _components)
	: IManageable(_data.name) 
{
	shape = new sf::RectangleShape(_data.size);
	shape->setFillColor(Color::White);
	shape->setPosition(_data.position);
	originalPosition = _data.position;
	components = _components;
	type = _data.type;
	isUpdatable = _isUpdatable;
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

bool Entity::ComputeIsOnScreen()
{
	sf::Vector2i _playerPosition(Game::GetInstance().GetPlayer()->GetCharacter()->GetPosition());
	sf::Vector2i _cameraViewSize(Camera::GetInstance().getSize());
	return (_playerPosition / _cameraViewSize == sf::Vector2i(shape->getPosition()) / _cameraViewSize);
	return true;
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
