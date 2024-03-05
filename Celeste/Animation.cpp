#include "Animation.h"
#include "AnimationComponent.h"
#include "Timer.h"
#include "Macro.h"
#include "Game.h"

Animation::Animation(const string& _name, AnimationComponent* _owner, Sprite* _sprite,
	const AnimationData& _data) : IManageable(_name)
{
	sprite = _sprite;
	Vector2i _position = Vector2i(static_cast<int>(_data.start.x), static_cast<int>(_data.start.y));
	Vector2i _size = Vector2i(static_cast<int>(_data.size.x), static_cast<int>(_data.size.y));
	IntRect _rect = IntRect(_position.x, _position.y, _size.x, _size.y);
	sprite->setTextureRect(_rect);
	owner = _owner;
	data = _data;
	Register();
}

Animation::~Animation()
{
	delete sprite;
	sprite = nullptr;
}


void Animation::Register()
{
	owner->Add(id, this);
}

void Animation::SetNext()
{
	if (!CanNext())
	{
		if (!data.canLoop)
		{
			Stop();
			return;
		}

		Reset();
	}

	currentIndex++;

	const Vector2i& _start = GetNewStart();
	const int _sizeX = static_cast<int>(data.size.x);
	const int _sizeY = static_cast<int>(data.size.y);
	const IntRect& _rect = IntRect(_start.x, _start.y, _sizeX, _sizeY);
	sprite->setTextureRect(_rect);
}

Vector2i Animation::GetNewStart()
{
	int _x = static_cast<int>(data.start.x);
	int _y = static_cast<int>(data.start.y);

	switch (data.readDirection)
	{
	case READ_DOWN:
		_y += static_cast<int>(currentIndex * data.size.y);
		break;

	case READ_RIGHT:
		_x += static_cast<int>(currentIndex * data.size.x);
		break;

	default:
		break;
	}

	return Vector2i(_x, _y);
}

void Animation::Start()
{
	timer = new Timer("Animation" + data.name, this, &Animation::SetNext, seconds(data.timeBetween), true, data.canLoop);
}

void Animation::Reset()
{
	currentIndex = -1;
}

void Animation::Stop()
{
	if (!timer) return;
	timer->Reset();
}

void Animation::Update()
{
	Vector2f _spriteSize = sprite->getLocalBounds().getSize();
	Vector2f _shapeSize = owner->GetOwner()->GetShape()->getLocalBounds().getSize();
	Vector2f _scale = Vector2f(_shapeSize.x / _spriteSize.x, _shapeSize.y / _spriteSize.y);
	sprite->setScale(_scale);
	sf::Vector2f _position = owner->GetOwner()->GetPosition();
	if (AnimationComponent* _component = dynamic_cast<AnimationComponent*>(owner))
	{
		if (dynamic_cast<Character*>(_component->GetOwner()))
			sprite->setPosition(Game::GetInstance().GetSenseOfGravity() == GRAVITY_NORMAL ? _position : sf::Vector2f(_position.x + _shapeSize.x, _position.y + _shapeSize.y));
		else
			sprite->setPosition(_position);
	}
	

}


