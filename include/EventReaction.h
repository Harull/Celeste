#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "IManageable.h"

class EventReactionManager;

class EventReaction : public IManageable<sf::Event::EventType>
{
	sf::Event::EventType eventType;
	std::vector<std::function<bool(const sf::Event& _event)>> callbacks;

public:
	EventReaction(const sf::Event::EventType& _eventType, const std::vector<std::function<bool(const sf::Event& _event)>>& _callbacks);
	EventReaction(const sf::Event::EventType& _eventType, const std::function<bool(const sf::Event& _event)>& _callback);

private:
	void Register();

public:
	bool ExecuteCallbacks(const sf::Event& _event);

	
};

