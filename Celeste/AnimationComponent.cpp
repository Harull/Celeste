#include "AnimationComponent.h"
#include <iostream>
#include "TextureManager.h"

AnimationComponent::AnimationComponent(Entity* _owner, const string& _path, const vector<AnimationData>& _animationsData,
	const AnimationDirection& _direction) : Component(_owner)
{
	InitAnimations(_path, _animationsData );
	currentIndex = -1;
	direction = _direction;
}


void AnimationComponent::InitAnimations(const string& _path, const vector<AnimationData>& _animationsData)
{
	for (const AnimationData& _data : _animationsData)
	{
		Sprite* _sprite = new Sprite();
		TextureManager::GetInstance().Load(_sprite, _path);
		new Animation(_data.name, this, _sprite, _data);
	}
}


void AnimationComponent::Update()
{
	for (Animation* _animation : GetAllValues())
	{
		_animation->Update();
	}

	const int _newIndex = GetNextIndex(direction);
	if (currentIndex == _newIndex) return;

	system("cls");

	if (currentIndex != -1)
	{
		Animation* _currentAnimation = GetCurrentAnimation();
		if (!_currentAnimation) return;
		cout << "Stop : " << _currentAnimation->GetData().name << endl;
		_currentAnimation->Stop();
		currentIndex = -1;
	}

	Animation* _animation = GetAllValues()[_newIndex];
	cout << "Start : " << _animation->GetData().name << endl;
	_animation->Start();
	currentIndex = _newIndex;
}