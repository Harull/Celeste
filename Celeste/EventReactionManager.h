#pragma once
#include "MultimapManager.h"
#include "EventReaction.h"
#include <SFML/Graphics.hpp>

class EventReactionManager : public MultimapManager<sf::Event::EventType, EventReaction, EventReactionManager>
{
public:
	static void BindNewInputReaction(const sf::Event::EventType& _eventType, const std::vector<std::function<bool(const sf::Event& _event)>>& _callbacks)
	{
		new EventReaction(_eventType, _callbacks);
	}	
	static void BindNewInputReaction(const sf::Event::EventType& _eventType, const std::function<bool(const sf::Event& _event)>& _callback)
	{
		new EventReaction(_eventType, _callback);
	}
	static void Add(const sf::Event::EventType& _key, EventReaction* _value)
	{
		GetInstance().InternAdd(_key, _value);
	}
	static std::vector<EventReaction*> GetValues(const sf::Event::EventType& _key)
	{
		return GetInstance().InternGetValues(_key);
	}
	static std::multimap<sf::Event::EventType, EventReaction*>& GetAllValues()
	{
		return GetInstance().InternGetAllValues();
	}
	static void DeleteAllAtKey(const sf::Event::EventType& _key)
	{
		GetInstance().InternDeleteAllAtKey(_key);
	}
	static void DeleteValue(EventReaction* _value)
	{
		GetInstance().InternDeleteValue(_value);
	}
	static void DeleteArrayOfValues(std::vector<EventReaction*>& _vectorToDelete)
	{
		GetInstance().InternDeleteArrayOfValues(_vectorToDelete);
	}
	static void Update(const sf::Event& _event)
	{
		std::vector<EventReaction*> _allReactions = EventReactionManager::GetValues(_event.type);
		for (EventReaction* _reaction : _allReactions)
		{
			_reaction->ExecuteCallbacks(_event);
		}
	}
};

