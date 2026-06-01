#include "../include/EntityManager.h"
#include "../include/MovingTile.h"

void EntityManager::Update()
{
	for (auto _entity : updatables)
	{
		if (_entity->ComputeIsOnScreen())
			_entity->Update();
	}
	
	/*for (Entity* _entity : GetAllValues())d
	{
		_entity->Update();
	}*/
	GarbageValues();
}

void EntityManager::Reset()
{
	for (auto _pair : allValues)
	{
		_pair.second->Reset();
	}
}

bool EntityManager::IsAvailable(const Vector2f& _position, const Vector2f& _size)
{
	/*const FloatRect& _rect = FloatRect(_position - _size / 2.0f, _size);
	for (auto _pair : allValues)
	{
		if (_pair.second->GetShape()->getLocalBounds().intersects(_rect)) return true;
	}
	return false;*/
	return 0;
}

void EntityManager::DisplayAllEntities() const
{
	/*sf::RenderWindow& _mainWindow = Game::GetWindow();
	const GameState& _gameState = Game::GetGameState();
	const auto& _allValues = GetAllValues();

	for (Entity* _entity : _allValues)
	{
		const std::vector<GameState>& _whendisplayed = _entity->GetWhenDisplayed();
		for (const GameState& _currentState : _whendisplayed)
		{
			if (_currentState == _gameState)
			{
				Game::SetViewState(_entity->GetViewState());
				_mainWindow.draw(*_entity->GetShape());
				break;
			}
		}
	}*/
}

vector<Entity*> EntityManager::GetAllEntites()
{
	vector<Entity*> _entities;
	for (auto _pair : allValues)
	{
		_entities.push_back(_pair.second);
	}
	return _entities;
}

void EntityManager::StopAnimation()
{
	for (Entity* _entity : GetAllValues())
	{
		if (AnimationComponent* _anim = _entity->GetComponent<AnimationComponent>())
		{
			_anim->Finish();
		}

	}
}

void EntityManager::ClearUpdatables()
{
	updatables.clear();
}

void EntityManager::RetrieveAllUpdatables()
{
	ClearUpdatables();
	for (auto _entities : allValues)
	{
		if (_entities.second->GetIsUpdatable())
			updatables.emplace_back(_entities.second);
	}
}
