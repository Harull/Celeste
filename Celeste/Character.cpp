#include "Character.h"
#include "TextureManager.h"
#include "MovementComponent.h"
#include "GravityComponent.h"
#include "AnimationComponent.h"
#include "CollisionComponent.h"
#include "TimerManager.h"
#include "Game.h"

#define CHARACTER_TEXTURE "Character/Slave.png"
#define DEAD_ZONE 50.f

Character::Character(const sf::Vector2f _size, const sf::Vector2f _position, const int _maxYVelocity, const bool _isVisible)
	: Entity(EntityData("Character", ENTITY_CHARACTER, _position, _size),
		{ new MovementComponent(this, 2.5f, sf::Vector2f(0,0), true),
			new GravityComponent(this, 4.5f),
			new CollisionComponent(this) })
{
	maxYVelocity = _maxYVelocity;
	currentYVelocity = 0;
	currentJumpTimerIndex = 0;
	checkPoint = Vector2f(0.f, 0.f);

	isJumping = false;
	isClimbing = false;
	isDashing = false;

	dashCount = 1;
	maxDashCount = 1;
	currentDashVelocity = _maxYVelocity * 2;
	currentDashTimerIndex = 0;
	dashDirectionBuffer = Vector2i(0, 0);

	InitShape();
	const Vector2f& _sizeA = Vector2f(24.4f, 41.f);
	const ReadDirection& _readDirection = READ_RIGHT;
	const bool _toRepeat = true;
	const int _count = 8;
	const int _countStop = 1;
	const float _speedA = 0.1f;
	AnimationDirection direction = ANIM_DIR_RIGHT;

	AnimationComponent* _animation = new AnimationComponent(this, CHARACTER_TEXTURE, {
		AnimationData("WalkRight", Vector2f(12.0f, 7.f), _sizeA, _readDirection, ANIM_DIR_RIGHT, _toRepeat, _count, _speedA),
		AnimationData("WalkLeft", Vector2f(11.f, 53.f), _sizeA, _readDirection, ANIM_DIR_LEFT, _toRepeat, _count, _speedA),
		AnimationData("JumpRight", Vector2f(12.f, 100.f), Vector2f(22.f,47.f), _readDirection, ANIM_DIR_JUMP_RIGHT, _toRepeat, _countStop, _speedA),
		AnimationData("FallRight", Vector2f(38.f, 102.f), Vector2f(23.f,44.f), _readDirection, ANIM_DIR_FALL_RIGHT, _toRepeat, _countStop, _speedA),
		AnimationData("JumpLeft", Vector2f(38.f, 151.f), Vector2f(23.f,47.f), _readDirection, ANIM_DIR_JUMP_LEFT, _toRepeat, _countStop, _speedA),
		AnimationData("FallLeft", Vector2f(13.f, 153), Vector2f(23.f,45.f), _readDirection, ANIM_DIR_FALL_LEFT, _toRepeat, _countStop, _speedA),

		AnimationData("GrabLeftWall", Vector2f(12.f, 396.f), Vector2f(21.f, 40.f), _readDirection, ANIM_DIR_GRAB_LEFT, _toRepeat, 1, _speedA * 2.f),
		AnimationData("GrabRightWall", Vector2f(12.f, 348.f), Vector2f(21.f, 40.f), _readDirection, ANIM_DIR_GRAB_RIGHT, _toRepeat, 1, _speedA * 2.f),
		AnimationData("ClimbLeftWall", Vector2f(12.f, 300.f), Vector2f(21.f, 40.f), _readDirection, ANIM_DIR_CLIMB_LEFT, _toRepeat, 4, _speedA * 2.f),
		AnimationData("ClimbRightWall", Vector2f(14.f, 252.f), Vector2f(21.f, 40.f), _readDirection, ANIM_DIR_CLIMB_RIGHT, _toRepeat, 4, _speedA * 2.f),

		AnimationData("DashRight", Vector2f(12.f, 455.f), Vector2f(25.f, 40.f), _readDirection, ANIM_DIR_DASH_RIGHT, _toRepeat, 8, _speedA),
		AnimationData("DashLeft", Vector2f(12.f, 503.f), Vector2f(25.f, 40.f), _readDirection, ANIM_DIR_DASH_LEFT, _toRepeat, 8, _speedA ),


		AnimationData("None", Vector2f(12.f, 203), _sizeA, _readDirection, ANIM_DIR_NONE, _toRepeat, 1, _speedA),
		}, direction);


	/* _name,  _start, _size,
		ReadDirection& _readDirection, AnimationDirection& _direction,
		bool _canLoop, int _count, float _timeBetween)*/


	components.push_back(_animation);
	shape->setOutlineThickness(2);
	shape->setOutlineColor(sf::Color::Red);
	shape->setFillColor(sf::Color::Transparent);
}

void Character::InitShape()
{
	TextureManager::GetInstance().Load(shape, CHARACTER_TEXTURE);
}

bool Character::MovingLeftRight(const sf::Event& _event)
{
	sf::Keyboard::Key _leftKey = sf::Keyboard::Q;
	sf::Keyboard::Key _rightKey = sf::Keyboard::D;

	if (_event.type != sf::Event::JoystickMoved)
		if (_event.key.code != _leftKey && _event.key.code != _rightKey)return false;

	MovementComponent* _mvComponent = GetComponent<MovementComponent>();
	if (isClimbing)
	{
		_mvComponent->SetDirection({ 0,0 });
		return false;
	}

	sf::Vector2f _direction = _mvComponent->GetDirection();


	float _xDirection;
	if (_event.type == sf::Event::JoystickMoved)
	{
		float _axisXPosition = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
		_xDirection = (_axisXPosition <= -DEAD_ZONE) ? -1.f : _axisXPosition >= DEAD_ZONE ? 1.f : 0.f;
	}
	else
		_xDirection = -(sf::Keyboard::isKeyPressed(_leftKey) * 1.f) + sf::Keyboard::isKeyPressed(_rightKey) * 1.f;

	sf::Vector2f _newDirection(_xDirection, _direction.y);
	_mvComponent->SetDirection(_newDirection);
	return true;
}

bool Character::Jump(const sf::Event& _event)
{
	sf::Keyboard::Key _jumpKey = sf::Keyboard::Space;
	if (_event.type == sf::Event::JoystickButtonPressed && _event.joystickButton.button != 0)return false;
	if (_event.type == sf::Event::KeyPressed && _event.key.code != _jumpKey)return false;

	if (isJumping || (!(GetComponent<CollisionComponent>()->CheckCollision().collisionSideBinary & COLLIDE_UP) && !isClimbing)) return false;
	isJumping = true;
	currentJumpTimerIndex = 0;

	Timer* _jumpTimer = new Timer("JumpTimer", [&]() {
		MovementComponent* _mvComponent = GetComponent<MovementComponent>();

		sf::Vector2f _direction = _mvComponent->GetDirection();
		float _xDirectionModif = 0.f;
		
		if (currentJumpTimerIndex == 0)
		{
			if (isClimbing)
			{
				CollisionInfos _collisionInfos = GetComponent<CollisionComponent>()->CheckCollision(true);
				_xDirectionModif = _collisionInfos.collisionSideBinary & COLLIDE_LEFT ? -5.f : 5.f;
			}
			currentYVelocity = maxYVelocity;
		}
		else
			currentYVelocity = maxYVelocity / ((currentJumpTimerIndex / 12) + 1);

		if (currentYVelocity < 2) return;

		
		_mvComponent->Move({ _xDirectionModif, -currentYVelocity * static_cast<float>(Game::GetInstance().GetSenseOfGravity())});
		currentJumpTimerIndex++;
		}, sf::seconds(0), true, true);

	return false;
}

bool Character::Dash(const sf::Event& _event)
{
	sf::Keyboard::Key _dashKey = sf::Keyboard::C;
	if (_event.type == sf::Event::JoystickButtonPressed && _event.joystickButton.button != 2)return false;
	if (_event.type == sf::Event::KeyPressed && _event.key.code != _dashKey)return false;

	if (isDashing || dashCount <= 0) return false;
	isDashing = true;
	dashCount--;
	currentDashTimerIndex = 0;

	sf::Keyboard::Key _up = sf::Keyboard::Z;
	sf::Keyboard::Key _left = sf::Keyboard::Q;
	sf::Keyboard::Key _down = sf::Keyboard::S;
	sf::Keyboard::Key _right = sf::Keyboard::D;

	MovementComponent* _mvComponent = GetComponent<MovementComponent>();
	sf::Vector2f _direction = _mvComponent->GetDirection();
	float _xDirectionModif = 0.f;

	if (_event.type == sf::Event::JoystickButtonPressed)
	{
		float _axisXPosition = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
		float _axisYPosition = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
		int _xDirection = (_axisXPosition <= -DEAD_ZONE) ? -1 : _axisXPosition >= DEAD_ZONE ? 1 : 0;
		int _YDirection = (_axisYPosition <= -DEAD_ZONE) ? -1 : _axisYPosition >= DEAD_ZONE ? 1 : 0;
		dashDirectionBuffer = { _xDirection, _YDirection };
	}
	else
	{
		dashDirectionBuffer = { -static_cast<int>(sf::Keyboard::isKeyPressed(_left)) + sf::Keyboard::isKeyPressed(_right),
								-static_cast<int>(sf::Keyboard::isKeyPressed(_up)) + sf::Keyboard::isKeyPressed(_down) };
	}

	if (auto _currentDashTimer = TimerManager::GetInstance().GetApproximately("DashTimer"))
	{
		currentDashTimerIndex = 0;
		currentDashVelocity = maxDashVelocity;
		_currentDashTimer->Reset();
	}
	else
	{
		Timer* _dashTimer = new Timer("DashTimer", [&]() {
		MovementComponent* _mvComponent = GetComponent<MovementComponent>();

		currentDashVelocity = maxYVelocity / ((currentDashTimerIndex / 10) + 1);

		if (currentDashVelocity < 2) return;

		_mvComponent->Move(sf::Vector2f(dashDirectionBuffer * currentDashVelocity), false);
		currentDashTimerIndex++;
		}, sf::seconds(0), true, true);

	}

	
	return false;
}

bool Character::Climb(const sf::Event& _event)
{
	sf::Keyboard::Key _climbKey = sf::Keyboard::V;
	sf::Keyboard::Key _upKey = sf::Keyboard::Z;
	sf::Keyboard::Key _downKey = sf::Keyboard::S;

	const CollisionInfos& _collisionInfo = GetComponent<CollisionComponent>()->CheckCollision(true);
	if (!(_collisionInfo.entityTypeBinary & ENTITY_TILE) || (!(_collisionInfo.collisionSideBinary & COLLIDE_RIGHT) && !(_collisionInfo.collisionSideBinary & COLLIDE_LEFT)))
	{
		isClimbing = false;
		return false;
	}

	if (_event.type == sf::Event::KeyPressed && _event.key.code != _climbKey && _event.key.code != _upKey && _event.key.code != _downKey)return false;

	if (_event.type == sf::Event::JoystickMoved && sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Z) >= 50)
	{
		isClimbing = true;
		if (Timer* _jumpTimer = TimerManager::GetInstance().GetApproximately("JumpTimer"))
		{
			_jumpTimer->Stop();
			isJumping = false;
		}
	}
	else if (_event.type == sf::Event::KeyPressed && _event.key.code == _climbKey)
	{
		isClimbing = true;
		if (Timer* _jumpTimer = TimerManager::GetInstance().GetApproximately("JumpTimer"))
		{
			_jumpTimer->Stop();
			isJumping = false;
		}
	}
	else if ((_event.type == sf::Event::KeyReleased && _event.key.code == _climbKey) ||  ((_event.type == sf::Event::JoystickMoved) && sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Z) <= 50))
	{
		isClimbing = false;
	}
	if (!isClimbing) return false;


	MovementComponent* _mvComponent = GetComponent<MovementComponent>();
	sf::Vector2f _direction = _mvComponent->GetDirection();

	float _yDirection;
	if (_event.type == sf::Event::JoystickMoved)
	{
		float _axisYPosition = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
		_yDirection = (_axisYPosition <= -DEAD_ZONE) ? -1.f : _axisYPosition >= DEAD_ZONE ? 1.f : 0.f;
	}
	else
		_yDirection = -(sf::Keyboard::isKeyPressed(_upKey) * 1.f) + sf::Keyboard::isKeyPressed(_downKey) * 1.f;

	sf::Vector2f _newDirection(_direction.x, _yDirection);

	_mvComponent->SetDirection(_newDirection);
	return true;
}

void Character::ResetJumpValues()
{
	isJumping = true;
	currentJumpTimerIndex = 0;
}

void Character::ResetDashValues()
{
	isDashing = false;
	currentDashTimerIndex = 0;
}

void Character::Update()
{
	if (isDie)
		Respawn();

	Entity::Update();
}

void Character::Die()
{
	if (Timer* _dashTimer = TimerManager::GetInstance().GetApproximately("DashTimer"))
	{
		_dashTimer->Stop();
		ResetDashValues();
	}
	
	isDie = true;

}

void Character::Respawn()
{
	shape->setPosition(checkPoint);
	isDie = false;
}
