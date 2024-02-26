#pragma once
#include <vector>
#include <string>
#include <functional>
#include <SFML/Graphics.hpp>
#include "IManageable.h"
#include "IManager.h"
#include "Singleton.h"

using namespace sf;
using namespace std;

typedef Event::EventType ActionType;

struct InputData
{
	ActionType type;
	int key;
};

struct ActionData
{
	string name;
	vector<InputData> keys;
	function<void()> callback;
	// ctrl / alt / win / shift	
	ActionData()
	{
		name = "Unknown";
		keys = vector<InputData>();
		callback = function<void()>();
	}

	template <class Class, typename RType = void, typename... Args>
	ActionData(const string& _name, Class* _owner, RType(Class::* _callback)(Args...), const InputData& _primaryKey, const InputData& _secondaryKey = InputData(), Args... _args)
	{
		name = _name;
		keys.push_back(_primaryKey);
		keys.push_back(_secondaryKey);
		callback = [_callback, _owner, _args...]() {
			return (_owner->*_callback)(_args...);
			};
	}

	ActionData(const string& _name, const function<void()>& _callback, const InputData& _primaryKey, const InputData& _secondaryKey = InputData())
	{
		name = _name;
		keys.push_back(_primaryKey);
		keys.push_back(_secondaryKey);
		callback = _callback;
	}

	bool operator !() const
	{
		return name == "Unknown";
	}

};

//template <typename RType>
struct Action : public IManageable<string>
{
	ActionData data;
	string actionMap;

	Action(const ActionData& _data, const string& _actionMap) : IManageable(_data.name)
	{
		if (!_data)
		{
			toRemove = true;
		}
		else
		{
			data = _data;
			actionMap = _actionMap;
		}
		Register();
	}


	virtual void Register() override;
	void Execute();

};

struct ActionMap : public IManageable<string>, public IManager<string, Action>
{
	vector<Action*> actions;

	ActionMap(const string& _name, const vector<ActionData>& _actionsData = vector<ActionData>()) : IManageable(_name)
	{
		Register();

		for (const ActionData& _actionData : _actionsData)
		{
			actions.push_back(new Action(_actionData, id));
		}
	}
private:
	virtual void Register() override;

public:
	void Update(const Event& _event);
};

class InputManager : public Singleton<InputManager>, public IManager<string, ActionMap>
{
	Vector2f mousePosition;

public:
	Vector2f GetMousePosition() const
	{
		return mousePosition;
	}

public:
	InputManager();

	bool UpdateWindow(RenderWindow& _window);

	void UpdateInput(const Event& _event);
};
