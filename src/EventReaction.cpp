#include "../include/EventReaction.h"
#include "../include/EventReactionManager.h"


EventReaction::EventReaction(const sf::Event::EventType& _eventType,
	const std::vector<std::function<bool(const sf::Event& _event)>>& _callbacks) : IManageable(_eventType)
{
	eventType = _eventType;
	callbacks = _callbacks;
	Register();
}

EventReaction::EventReaction(const sf::Event::EventType& _eventType,
	const std::function<bool(const sf::Event& _event)>& _callback) : IManageable(_eventType)
{
	eventType = _eventType;
	callbacks = std::vector<std::function<bool(const sf::Event& _event)>>();
	callbacks.push_back(_callback);
	Register();
}


void EventReaction::Register()
{
	EventReactionManager::Add(id, this);
}

bool EventReaction::ExecuteCallbacks(const sf::Event& _event)
{
	for (auto _callback : callbacks)
	{
		if(_callback(_event)) return true;
	}
	return false;
}

