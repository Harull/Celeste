#pragma once
#include <map>
#include <vector>
#include "Singleton.h"
#include "SFML/Graphics.hpp"
#include <string>

template<typename Key, typename Value, typename ClassType>
class MultimapManager : public Singleton<ClassType>
{
private:
	std::multimap<Key, Value*> allValues;

public:
	~MultimapManager()
	{
		for (auto& _value : allValues)
		{
			delete _value.second;
			_value.second = nullptr;
		}
	}

protected:
	void InternAdd(const Key& _key, Value* _value)
	{
		allValues.insert(std::pair<Key, Value*>(_key, _value));
	}
	void InternRemoveAllAtKey(const Key& _key)
	{
		allValues.erase(_key);
	}
	std::vector<Value*> InternGetValues(const Key& _key)
	{
		if (!InternExist(_key))return std::vector<Value*>();
		std::vector<Value*> vectorValues;
		for (std::pair<Key, Value*> _pair : allValues)
		{
			if (_key == _pair.first) vectorValues.push_back(_pair.second);
		}
		return vectorValues;
	}
	bool InternExist(const Key& _key) const
	{
		return allValues.find(_key) != allValues.end();
	}
	std::multimap<Key, Value*>& InternGetAllValues()
	{
		return allValues;
	}
	void InternDeleteAllAtKey(const Key& _key)
	{
		std::vector<Value*> _values = InternGetValues(_key);
		InternRemoveAllAtKey(_key);
		for (auto& _value : _values)
		{
			delete _value;
			_value = nullptr;
		}
	}
	void InternDeleteValue(Value*& _value)
	{
		for (auto _it = allValues.begin(); _it != allValues.end(); _it++)
		{
			if ((*_it).second == _value)
			{
				allValues.erase(_it);
				delete _value;
				_value = nullptr;
				return;
			}
		}
	}
	void InternDeleteArrayOfValues(std::vector<Value*>& _vectorToDelete)
	{
		for (auto& _val : _vectorToDelete)
		{
			InternDeleteValue(_val);
		}
	}

	void InternClear() {
		for (auto& _value : allValues) {
			delete _value.second;
		}
		allValues.clear();
	}
};
