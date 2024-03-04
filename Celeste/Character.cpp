#include "Character.h"
#include "TextureManager.h"
#include "MovementComponent.h"
#include "GravityComponent.h"
#include "AnimationComponent.h"
#include "CollisionComponent.h"
#include "TimerManager.h"

#define CHARACTER_TEXTURE "Character/Slave.png"


Character::Character(const sf::Vector2f _size, const sf::Vector2f _position, const int _maxYVelocity, const bool _isVisible)
	: Entity(EntityData("Character", ENTITY_CHARACTER, _position, _size),
		{ new MovementComponent(this, 2.5f, sf::Vector2f(0,0), true),
			new GravityComponent(this, 4.5f),
			new CollisionComponent(this) })
{
	isJumping = false;
	maxYVelocity = _maxYVelocity;
	currentYVelocity = 0;
	currentJumpTimerIndex = 0;
	checkPoint = Vector2f(0.f, 0.f);

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
		AnimationData("None", Vector2f(12.f, 203), _sizeA, _readDirection, ANIM_DIR_NONE, _toRepeat, 1, _speedA),
		}, direction);

	components.push_back(_animation);
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
		_mvComponent->SetDirection({0,0});
		return false;
	}
	
	sf::Vector2f _direction = _mvComponent->GetDirection();


	float _xDirection;
	if (sf::Joystick::isConnected(0) && _event.type == sf::Event::JoystickMoved)
	{
		float _axisXPosition = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
		_xDirection = (_axisXPosition <= -50.f) ? -1.f : _axisXPosition >= 50.f ? 1.f : 0.f;
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
	if (_event.key.code != _jumpKey)return false;

	//std::cout << GetComponent<CollisionComponent>()->CheckCollision().collisionSideBinary << std::endl;
	if (isJumping || !(GetComponent<CollisionComponent>()->CheckCollision().collisionSideBinary & COLLIDE_UP)) return false;
	isJumping = true;
	currentJumpTimerIndex = 0;

	Timer* _jumpTimer = new Timer("JumpTimer", [&]() {
		MovementComponent* _mvComponent = GetComponent<MovementComponent>();
		sf::Vector2f _direction = _mvComponent->GetDirection();

		if (currentJumpTimerIndex == 0)
			currentYVelocity = maxYVelocity;
		else
			currentYVelocity = maxYVelocity / ((currentJumpTimerIndex / 12) + 1);

		if (currentYVelocity < 2) return;


		_mvComponent->Move({ 0, -currentYVelocity * 1.f });
		/*sf::Vector2f _newDirection(_direction.x, -currentYVelocity * 1.f);
		if (_direction.y > _newDirection.y)
			_mvComponent->SetDirection(_newDirection);*/

		currentJumpTimerIndex++;
		}, sf::seconds(0), true, true);

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

	if (_event.key.code == _climbKey)
	{
		if (_event.type == sf::Event::KeyPressed)
		{
			isClimbing = true;
			if (Timer* _jumpTimer = TimerManager::GetInstance().GetApproximately("JumpTimer"))
			{
				_jumpTimer->Stop();
				isJumping = false;
			}
		}
		else
		{
			isClimbing = false;
			GetComponent<MovementComponent>()->SetDirection({0,0});
		}
	}

	if (!isClimbing) return false;


	MovementComponent* _mvComponent = GetComponent<MovementComponent>();
	sf::Vector2f _direction = _mvComponent->GetDirection();

	float _yDirection = -(sf::Keyboard::isKeyPressed(_upKey) * 1.f) + sf::Keyboard::isKeyPressed(_downKey) * 1.f;
	sf::Vector2f _newDirection(_direction.x, _yDirection);

	_mvComponent->SetDirection(_newDirection);

	return true;
}

void Character::ResetJumpValues()
{
	isJumping = true;
	currentJumpTimerIndex = 0;
}

void Character::Update()
{
	Entity::Update();
}

void Character::SetPosition(const sf::Vector2f& newPosition)
{
	shape->setPosition(newPosition);
}
