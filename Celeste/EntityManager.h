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
				_drawables.push_back(_entity->GetShape());
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
					_drawables.push_back(_entity->GetShape());
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
};

