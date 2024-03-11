#include "Camera.h"
#include "Player.h"
#include "Macro.h"
#include "Game.h"
#include "TimerManager.h"
#include "MovementComponent.h"
#include"EntityManager.h"
#include "MapManager.h"

void Camera::Init(const Vector2f& _position, const Vector2f& _size)
{
	previousIndexes = { 0,0 };
	move(_position);
	setSize(_size);
	setCenter(_size/2.f);
}

void Camera::Update(bool _heroTeleport)
{
	Game& _game = Game::GetInstance();
	const sf::Vector2f _playerPosition = _game.GetPlayer()->GetCharacter()->GetPosition();
	const sf::Vector2i _index(static_cast<int>(std::floor(_playerPosition.x / 1920)), static_cast<int>(std::floor(_playerPosition.y / 1080)));
	
	Timer* _jumpTimer = TimerManager::GetInstance().GetApproximately("JumpTimer");
	
	std::vector<std::vector<SmallMap*>> _currentMap = MapManager::GetInstance().GetCurrent()->GetMaps();

	if (previousIndexes.x != _index.x || previousIndexes.y != _index.y)
	{
		if (_index.y < 0 || _currentMap.size() - 1 < _index.y)
		{
			_game.GetPlayer()->GetCharacter()->Die();
			return;
		}
		else if (_index.x < 0 || _currentMap[_index.y].size() - 1 < _index.x)
		{
			_game.GetPlayer()->GetCharacter()->Die();
			return;
		}
		/*else if (!_currentMap[_index.y][_index.x])
		{
			_game->GetPlayer()->GetCharacter()->Die();
			return;
		}*/
	}
	

	if (previousIndexes.x != _index.x)
	{
		const int _sign = _index.x - previousIndexes.x;

		if (_jumpTimer)
			_jumpTimer->Pause();

		while (!IsNearlyEqual(getCenter().x, _index.x * getSize().x + getSize().x / 2.f))
		{
			if (!_heroTeleport)
			{
			_game.UpdateSnow();
			_game.UpdateWindow();

			}
			move(_sign * 0.8f , 0);
		}
			EntityManager::GetInstance().Reset();

		if (_jumpTimer)
			_jumpTimer->Start();
	}
	 if (previousIndexes.y != _index.y)
	{
		const int _sign = _index.y - previousIndexes.y;
		while (!IsNearlyEqual(getCenter().y, _index.y * getSize().y + getSize().y / 2.f))
		{
			if (!_heroTeleport)
			{
				_game.UpdateSnow();
				_game.UpdateWindow();

			}
			
			move(0, _sign * 0.5f);
		}
			EntityManager::GetInstance().Reset();
		if (_sign <= 0)
		{
			if (_jumpTimer)
			{
				_game.GetPlayer()->GetCharacter()->ResetJumpValues();
				_jumpTimer->Reset();
			}
		}
		else if (_jumpTimer)
		{
			_jumpTimer->Stop();
			_game.GetPlayer()->GetCharacter()->GetComponent<MovementComponent>()->Move();
		}
	}

	
	previousIndexes = _index;
}
