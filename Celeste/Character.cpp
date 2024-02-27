#include "Character.h"
#include "TextureManager.h"

#define CHARACTER_TEXTURE "Character/Slave.png"

//Character::Character()
//	: Entity(EntityData("Character", Vector2f(), Vector2f()))
//{
//}

Character::Character(const sf::Vector2f _size, const sf::Vector2f _position, const bool _isVisible)
	: Entity(EntityData("Character", _position, _size))
{
	//TODO envoyer la shape à l'entity
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

void Character::InitComponents()
{
	components.reserve(3);

	//TODO set Components

	/*components.emplace_back(new MovementComponent);
	components.emplace_back(new GravityComponent);*/
}

void Character::Update()
{
	Entity::Update();
}
