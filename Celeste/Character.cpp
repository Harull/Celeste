#include "Character.h"
#include "TextureManager.h"
#include "MovementComponent.h"
#include "GravityComponent.h"
#include "AnimationComponent.h"
#include "CollisionComponent.h"

#define CHARACTER_TEXTURE "Character/Slave.png"


Character::Character(const sf::Vector2f _size, const sf::Vector2f _position, const bool _isVisible)
	: Entity(EntityData("Character", _position, _size),
		{ new MovementComponent(this, 0.1f, sf::Vector2f(0,0), true),
			new GravityComponent(this, 0.0005f),
			new CollisionComponent(this)})
{
	isVisible = _isVisible;
	//shape = new RectangleShape(_size);
	InitShape();
	const Vector2f& _sizeA = Vector2f(_size);
	const ReadDirection& _readDirection = READ_RIGHT;
	const bool _toRepeat = true;
	const int _count = 10;
	const int _countStop = 3;
	const float _speedA = 0.1f;
	direction = ANIM_DIR_DOWN;

	animation = new AnimationComponent(this, CHARACTER_TEXTURE, {
		AnimationData("WalkDown", Vector2f(0.0f, 232.5f), _sizeA, _readDirection, ANIM_DIR_DOWN, _toRepeat, _count, _speedA),
		AnimationData("WalkLeft", Vector2f(0.0f, 290.5f), _sizeA, _readDirection, ANIM_DIR_LEFT, _toRepeat, _count, _speedA),
		AnimationData("WalkUp", Vector2f(0.0f, 348.5f), _sizeA, _readDirection, ANIM_DIR_UP, _toRepeat, _count, _speedA),
		AnimationData("WalkRight", Vector2f(0.0f, 406.5f), _sizeA, _readDirection, ANIM_DIR_RIGHT, _toRepeat, _count, _speedA),
		AnimationData("NONE", Vector2f(0.0f, 0.0f), _sizeA, _readDirection, ANIM_DIR_NONE, _toRepeat, _countStop, _speedA),
		}, direction);

	components.push_back(animation);

	//InitComponents();

	//Update();

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
	std::cout << sf::Keyboard::isKeyPressed(_leftKey) << " | " << sf::Keyboard::isKeyPressed(_rightKey) << std::endl;

	float _xDirection = -(sf::Keyboard::isKeyPressed(_leftKey) * 1.f) + sf::Keyboard::isKeyPressed(_rightKey) * 1.f;
	std::cout << _xDirection << std::endl;
	sf::Vector2f _newDirection(_xDirection, _direction.y);

	_mvComponent->SetDirection(_newDirection);
	return true;
}

void Character::Update()
{
	Entity::Update();
}
