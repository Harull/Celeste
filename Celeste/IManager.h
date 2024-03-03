#pragma once
#include<map>
#include<vector>
#include <string>

using namespace std;

template <typename Key, typename Value>
class IManager
{
	Value* current;
protected:
	map<Key, Value*> allValues;
	vector<Value*> unregisteredValues;
	Value* selectedValue;

public:
	Value* GetSelected()
	{
		return selectedValue;
	}

public:
	~IManager()
	{
		for (auto _pair : allValues)
		{
			if (_pair.second)return;
			delete _pair.second;
			_pair.second = nullptr;
		}

		for (Value* _value : unregisteredValues)
		{
			delete _value;
		}
	}

public:
	void Add(const Key& _key, Value* _value)
	{
		if (Exist(_value))
		{
			unregisteredValues.push_back(_value);
			return;
		}
		allValues[_key] = _value;
		current = _value;
		_value->SetID(_key);
	}
	void Remove(Value* _value)
	{
		if (!Exist(_value))return;

		const Key& _key = _value->GetID();
		delete _value;
		allValues[_value->GetID()] = nullptr;
		allValues.erase(_key);
	}
	/* void Remove(const Key& _key)
	 {
		 if (!Exist(_key))return;
		 delete allValues[_key];
		 allValues[_key] = nullptr;
		 allValues.erase(_key);
	 }*/
	Value* Get(const Key& _key)
	{
		if (!Exist(_key))return nullptr;
		return allValues[_key];

	}
	Value* GetApproximately(const Key& _key)
	{
		for (auto _value : allValues)
		{
			if (Contain(_value.first, _key))
			{
				return _value.second;
			}
		}
		return nullptr;
	}
	bool Contain(const std::string& _id, const std::string& _value)
	{
		if (_id.find(_value) != std::string::npos)
		{
			return true;
		}
		return false;
	}
	map<Key, Value*> GetAll() const
	{
		return allValues;
	}
	Value* GetCurrent()
	{
		return current;
	}
	bool Exist(const Key& _key)
	{
		return allValues.find(_key) != allValues.end();
	}
	bool Exist(Value* _value)
	{
		return Exist(_value->GetID());
	}


	void Remove(const Key& _key)
	{
		if (!Exist(_key)) return;
		allValues[_key]->SetToRemove(true);
	}
	void GarbageValues()
	{
		vector<Key> _keysToRemove;
		for (const auto& _pair : allValues)
		{
			if (_pair.second->IsToRemove())
			{
				_keysToRemove.push_back(_pair.first);
			}
		}

		for (const Key& _key : _keysToRemove)
		{
			Value* _value = allValues[_key];
			allValues.erase(_key);
			delete _value;
		}
	}
	int Count() const
	{
		return static_cast<int>(allValues.size());
	}
	vector<Value*> GetAllValues() const
	{
		vector<Value*> _values;

		for (const auto& _pair : allValues)
		{
			_values.push_back(_pair.second);
		}

		return _values;
	}

	void Clear() {

		for (auto& _value : allValues) {
			delete _value.second;
		}
		allValues.clear();

	}

};
