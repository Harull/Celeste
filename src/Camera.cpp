#include "Camera.h"
#include "Player.h"
#include "Macro.h"
#include "Game.h"
#include "TimerManager.h"
#include "MovementComponent.h"
#include "EntityManager.h"


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
		Game& _game = Game::GetInstance();
		if (_game.GetSenseOfGravity() == GRAVITY_INVERTED)
		{
			_game.ToggleSenseOfGravity();
		}
		const int _sign = _index.x - previousIndexes.x;

		if (_jumpTimer)
			_jumpTimer->Pause();

		while (!IsNearlyEqual(getCenter().x, _index.x * getSize().x + getSize().x / 2.f))
		{
			if (!_heroTeleport)
			{
			_game.UpdateSnow();
			_game.UpdateWindow(false);

			}
			move(_sign * 1.5f , 0);
		}
			EntityManager::GetInstance().Reset();

		if (_jumpTimer)
			_jumpTimer->Start();
	}
	 if (previousIndexes.y != _index.y)
	{
		 Game& _game = Game::GetInstance();
		 if (_game.GetSenseOfGravity() == GRAVITY_INVERTED)
		 {
			 _game.ToggleSenseOfGravity();
		 }
		const int _sign = _index.y - previousIndexes.y;
		while (!IsNearlyEqual(getCenter().y, _index.y * getSize().y + getSize().y / 2.f))
		{
			if (!_heroTeleport)
			{
				_game.UpdateSnow();
				_game.UpdateWindow(false);

			}
			
			move(0, _sign * 1.2f);
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
			//std::cout << "Move Camera" << std::endl;
			_game.GetPlayer()->GetCharacter()->GetComponent<MovementComponent>()->Move();
		}
	}

	
	previousIndexes = _index;
	UpdateMapAround(_currentMap);

}

void Camera::UpdateMapAround(const vector<vector<SmallMap*>>& _maps)
{
	vector<SmallMap*> _mapArround;

	_mapArround.push_back(_maps[previousIndexes.y][previousIndexes.x]);
	if (previousIndexes.x>=1)
	{
		_mapArround.push_back(_maps[previousIndexes.y][previousIndexes.x - 1]);

	}
	if (previousIndexes.x<=_maps[previousIndexes.y].size() - 2)
	{
		_mapArround.push_back(_maps[previousIndexes.y][previousIndexes.x+1]);

	}
	if (previousIndexes.y >= 1)
	{
		_mapArround.push_back(_maps[previousIndexes.y - 1][previousIndexes.x]);

	}
	int _max = static_cast<int>(_maps.size()) - 2;
	if (previousIndexes.y <= _max)
	{
		_mapArround.push_back(_maps[previousIndexes.y + 1][previousIndexes.x]);

	}
	
	mapAround = _mapArround;
}
