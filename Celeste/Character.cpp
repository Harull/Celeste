#include "Character.h"
#include "TextureManager.h"
#include "MovementComponent.h"
#include "GravityComponent.h"
#include "AnimationComponent.h"
#include "CollisionComponent.h"

#define CHARACTER_TEXTURE "Assets/Texture/Madeline.png"

Character::Character(const sf::Vector2f _size, const sf::Vector2f _position, const bool _isVisible)
	: Entity(EntityData("Character", _position, _size),
		{ new MovementComponent(this, 0.1f, sf::Vector2f(0,0), true),
			new GravityComponent(this, 0.0005f),
			new CollisionComponent(this)
		/* Todo, mettre le animation component*/})
{
	isVisible = _isVisible;

	InitShape();

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
