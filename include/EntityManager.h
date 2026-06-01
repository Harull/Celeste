#pragma once

#include "Singleton.h"
#include "IManager.h"
#include "Entity.h"
#include "Game.h"
#include"Camera.h"
using namespace std;

//typedef int ID;

class EntityManager : public Singleton<EntityManager>, public IManager<string, Entity>
{
	std::vector<Entity*> updatables;

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
		for (SmallMap* _map : Camera::GetInstance().GetMapsAround())
		{
			Grid* _grid = _map->GetGrid();
			_drawables.push_back(_grid->GetBackGround()->GetShape());
			for (Entity* _entity : _grid->GetTilesMap())
			{
				if (!_entity)continue;
				if (_visibleArea.intersects(_entity->GetShape()->getGlobalBounds())) {
					if (AnimationComponent* _animation = _entity->GetComponent<AnimationComponent>())
					{
						if (!_animation->GetCurrentAnimation())continue;
						

						_drawables.push_back(_animation->GetCurrentAnimation()->GetSprite());
					}
					else
					{
						_drawables.push_back(_entity->GetShape());
					}
				}

			}
			/*for (Entity* _entity : Camera::GetInstance().UpdateMapAround())
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
			}*/

		}
		Character* _hero = Game::GetInstance().GetPlayer()->GetCharacter();
		AnimationComponent* _animation = _hero->GetComponent<AnimationComponent>();
		
		
			_animation->GetCurrentAnimation()->GetSprite()->setColor(_hero->GetHasDashes() ? sf::Color::White : sf::Color(247, 94, 166, 255));
			_drawables.push_back(_animation->GetCurrentAnimation()->GetSprite());
			return _drawables;
	}

	std::vector<Entity*> GetUpdatables()const
	{
		return updatables;
	}
public:
	void Update();
	void Reset();
	bool IsAvailable(const Vector2f& _position, const Vector2f& _size);
	void DisplayAllEntities() const;
	vector<Entity*> GetAllEntites();
	void StopAnimation();
	
	void ClearUpdatables();
	void RetrieveAllUpdatables();

};

