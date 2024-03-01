#include "Character.h"
#include "TextureManager.h"
#include "MovementComponent.h"
#include "GravityComponent.h"
#include "AnimationComponent.h"
#include "CollisionComponent.h"

#define CHARACTER_TEXTURE "Character/Slave.png"


Character::Character(const sf::Vector2f _size, const sf::Vector2f _position, const bool _isVisible)
	: Entity(EntityData("Character", ENTITY_CHARACTER, _position, _size),
		{ new MovementComponent(this, 0.5f, sf::Vector2f(0,0), true),
			new GravityComponent(this, 0.8f),
			new CollisionComponent(this)})
{
	isVisible = _isVisible;
	InitShape();
	const Vector2f& _sizeA = Vector2f(24.4f,45.f);
	const ReadDirection& _readDirection = READ_RIGHT;
	const bool _toRepeat = true;
	const int _count = 8;
	const int _countStop = 1;
	const float _speedA = 0.1f;
	AnimationDirection direction = ANIM_DIR_RIGHT;

	AnimationComponent* _animation = new AnimationComponent(this, CHARACTER_TEXTURE, {
		AnimationData("WalkRight", Vector2f(12.0f, 7.f), _sizeA, _readDirection, ANIM_DIR_RIGHT, _toRepeat, _count, _speedA),
		AnimationData("WalkLeft", Vector2f(11.f, 53.f), _sizeA, _readDirection, ANIM_DIR_LEFT, _toRepeat, _count, _speedA),
		AnimationData("JumpRight", Vector2f(12.f, 101.f), _sizeA, _readDirection, ANIM_DIR_JUMP_RIGHT, _toRepeat, _countStop, _speedA),
		AnimationData("FallRight", Vector2f(36.f, 101.f), _sizeA, _readDirection, ANIM_DIR_FALL_RIGHT, _toRepeat, _countStop, _speedA),
		AnimationData("JumpLeft", Vector2f(38.f, 153.f), _sizeA, _readDirection, ANIM_DIR_JUMP_LEFT, _toRepeat, _countStop, _speedA),
		AnimationData("FallLeft", Vector2f(12.f, 153.f), _sizeA, _readDirection, ANIM_DIR_FALL_LEFT, _toRepeat, _countStop, _speedA),
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
	MovementComponent* _mvComponent = GetComponent<MovementComponent>();
	sf::Keyboard::Key _leftKey = sf::Keyboard::Q;
	sf::Keyboard::Key _rightKey = sf::Keyboard::D;


	if (_event.key.code != _leftKey && _event.key.code != _rightKey)return false;
	
	sf::Vector2f _direction = _mvComponent->GetDirection();

	float _xDirection = -(sf::Keyboard::isKeyPressed(_leftKey) * 1.f) + sf::Keyboard::isKeyPressed(_rightKey) * 1.f;
	sf::Vector2f _newDirection(_xDirection, _direction.y);

	_mvComponent->SetDirection(_newDirection);
	return true;
}

bool Character::Jump(const sf::Event& _event)
{
	MovementComponent* _mvComponent = GetComponent<MovementComponent>();
	sf::Keyboard::Key _jumpKey = sf::Keyboard::Space;

	if (_event.key.code != _jumpKey)return false;
	sf::Vector2f _direction = _mvComponent->GetDirection();

	sf::Vector2f _newDirection(_direction.x, -20.f);
	_mvComponent->SetDirection(_newDirection);
	return false;
}

void Character::Update()
{
	Entity::Update();
	
}

