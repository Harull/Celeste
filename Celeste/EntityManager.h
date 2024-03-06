#pragma once

#include "Singleton.h"
#include "IManager.h"
#include "Entity.h"
#include "Game.h"

using namespace std;

//typedef int ID;

class EntityManager : public Singleton<EntityManager>, public IManager<string, Entity>
{
public:
	vector<Drawable*> GetDrawables() const
	{
		vector<Drawable*> _drawables;

		for (Entity* _entity : GetAllValues())
		{
			if (AnimationComponent* _animation = _entity->GetComponent<AnimationComponent>())
			{
				if (Character* _currentCharacter = dynamic_cast<Character*>(_animation->GetOwner()))
				{
					_animation->GetCurrentAnimation()->GetSprite()->setColor(_currentCharacter->GetHasDashes() ? sf::Color::White : sf::Color(247, 94, 166, 255));
				}
				_drawables.push_back(_animation->GetCurrentAnimation()->GetSprite());
				
			}
			else
			{
				_drawables.push_back(_entity->GetShape());
			}
		}

		return _drawables;
	}


	vector<Drawable*> GetDrawables(FloatRect _visibleArea) const
	{
		vector<Drawable*> _drawables;

		for (Entity* _entity : GetAllValues())
		{
			if (_visibleArea.intersects(_entity->GetShape()->getGlobalBounds())) {
				if (AnimationComponent* _animation = _entity->GetComponent<AnimationComponent>())
				{
					if (!_animation->GetCurrentAnimation())continue;
					if (Character* _currentCharacter = dynamic_cast<Character*>(_animation->GetOwner()))
					{
						_animation->GetCurrentAnimation()->GetSprite()->setColor(_currentCharacter->GetHasDashes() ? sf::Color::White : sf::Color(247, 94, 166, 255));
					}
					
					_drawables.push_back(_animation->GetCurrentAnimation()->GetSprite());
				}
				else
				{
					_drawables.push_back(_entity->GetShape());
				}
			}
		}

		return _drawables;
	}
public:
	void Update();
	bool IsAvailable(const Vector2f& _position, const Vector2f& _size);
	void DisplayAllEntities() const;
	vector<Entity*> GetAllEntites();
	void StopAnimation();
	
};

