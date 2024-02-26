#pragma once

#include "IManageable.h"
#include <iostream>
#include <SFML/Graphics.hpp>


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

	EntityData(const string& _name, const Vector2f& _position, const Vector2f& _size, const string& _path = "") 
	{
		name = _name;
		position = _position;
		size = _size;
		path = _path;
	}
};

class Entity : public IManageable<string> 
{
protected:
	Texture texture;
	ViewState state;
	vector<Component*> components;
	Shape* shape;
	
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
	ViewState GetViewState()const
	{
		return state;
	}
	Vector2f GetPosition()const
	{
		return shape->getPosition();
	}

	Shape* GetShape()const
	{
		return shape;
	}

public:
	Entity(const EntityData& _data);
	~Entity();

private:
	void Register();

public:
	virtual void Update();
};

