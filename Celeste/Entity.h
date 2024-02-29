#pragma once

#include "IManageable.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "EntityType.h"
#include<functional>


using namespace std;
using namespace sf;

class Component;

enum ViewState;

struct EntityData
{
	string name;
	Vector2f position;
	Vector2f size;
	string path;
	EntityType type;

	EntityData(const string& _name, const EntityType _type, const Vector2f& _position, const Vector2f& _size, const string& _path = "")
	{
		name = _name;
		position = _position;
		size = _size;
		path = _path;
		type = _type;
	}
};

class Entity : public IManageable<string> 
{
protected:
	Texture texture;
	vector<Component*> components;
	Shape* shape;
	EntityType type;
	function<void(int _collisionSide, int _collisionSideBinary)>collisionReaction;
	
public:
	template<typename T>
	T* GetComponent() const
	{
		for (Component* _currentComponent : components)
		{
			if (T* _component = dynamic_cast<T*>(_currentComponent))
			{
				return _component;
			}
		}
		return nullptr;
	}
	
	Vector2f GetPosition()const
	{
		return shape->getPosition();
	}

	Shape* GetShape()const
	{
		return shape;
	}
	function<void(int _collisionSide, int _collisionSideBinary)> GetCollisionReaction()
	{
		return collisionReaction;
	}
	EntityType GetType()const
	{
		return type;
	}

public:
	Entity(const EntityData& _data, std::vector<Component*> _components = vector<Component*>());
	~Entity();

private:
	void Register();

public:
	virtual void Update();
};

