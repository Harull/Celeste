#include "Camera.h"
#include "Player.h"
#include "Macro.h"
#include "Game.h"
#include "TimerManager.h"
#include "MovementComponent.h"

void Camera::Init(const Vector2f& _position, const Vector2f& _size)
{
	previousIndexes = { 0,0 };
	move(_position);
	setSize(_size);
	setCenter(_size/2.f);
}

void Camera::Update(Game* _game)
{
	const sf::Vector2f _playerPosition = _game->GetPlayer()->GetCharacter()->GetPosition();
	const sf::Vector2f _index(std::floor(_playerPosition.x / 1920), std::floor(_playerPosition.y / 1080));
	
	Timer* _jumpTimer = TimerManager::GetInstance().GetApproximately("JumpTimer");
	

	if (previousIndexes.x != _index.x)
	{
		const float _sign = _index.x - previousIndexes.x;

		if (_jumpTimer)
			_jumpTimer->Pause();

		while (!IsNearlyEqual(getCenter().x, _index.x * 1920.f + 1920.f / 2.f))
		{
			_game->UpdateWindow();
			move(_sign * 0.6f , 0);
		}

		if (_jumpTimer)
			_jumpTimer->Start();
	}
	else if (previousIndexes.y != _index.y)
	{
		const float _sign = _index.y - previousIndexes.y;
		while (!IsNearlyEqual(getCenter().y, _index.y * 1080.f + 1080.f / 2.f))
		{
			_game->UpdateWindow();
			move(0, _sign * 0.4f);
		}
		if (_sign <= 0)
		{
			if (_jumpTimer)
			{
				_game->GetPlayer()->GetCharacter()->ResetJumpValues();
				_jumpTimer->Reset();
			}
		}
		else if (_jumpTimer)
		{
			_jumpTimer->Stop();
			_game->GetPlayer()->GetCharacter()->GetComponent<MovementComponent>()->Move();
		}
	}

	previousIndexes = _index;
}
