#pragma once
#include "IManageable.h"
#include "Timer.h"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class AnimationComponent;

enum AnimationDirection
{
	ANIM_DIR_NONE, ANIM_DIR_JUMP_LEFT, ANIM_DIR_JUMP_RIGHT, ANIM_DIR_LEFT, ANIM_DIR_RIGHT, ANIM_DIR_FALL_LEFT, ANIM_DIR_FALL_RIGHT, 
	ANIM_DIR_GRAB_LEFT, ANIM_DIR_GRAB_RIGHT, ANIM_DIR_CLIMB_LEFT, ANIM_DIR_CLIMB_RIGHT,
	ANIM_DIR_DASH_LEFT, ANIM_DIR_DASH_RIGHT, ANIM_DIR_STANDBY, ANIM_DIR_APPEARS, ANIM_DIR_DISAPPEARS, ANIM_DIR_IN_PORTAL, ANIM_DIR_OUT_PORTAL, ANIM_DIR_INVICIBLE, ANIM_TAUNT_UP, ANIM_TAUNT_DOWN, ANIM_TAUNT_LEFT, ANIM_TAUNT_RIGHT
};

enum ReadDirection
{
	READ_DOWN, READ_RIGHT
};

struct AnimationData
{
	bool canLoop;
	int count;
	float timeBetween;
	string name;
	Vector2f start;
	Vector2f size;
	ReadDirection readDirection;
	AnimationDirection direction;
	AnimationDirection nextDirection;

	AnimationData() = default;
	AnimationData(const string& _name, const Vector2f& _start, const Vector2f& _size,
		const ReadDirection& _readDirection, const AnimationDirection& _direction,
		const bool _canLoop, const int _count, const float _timeBetween,  AnimationDirection _nextDirection= AnimationDirection (- 1))
	{
		name = _name;
		start = _start;
		size = _size;
		readDirection = _readDirection;
		direction = _direction;
		canLoop = _canLoop;
		count = _count;
		timeBetween = _timeBetween;
		nextDirection = _nextDirection;
	}
};

class Animation : public IManageable<string>
{
	AnimationComponent* owner;
	int currentIndex;
	string path;
	AnimationData data;
	Sprite* sprite;
	Timer* timer;

public:
	AnimationData GetData() const
	{
		return data;
	}
	bool CanNext() const
	{
		return currentIndex < data.count - 1;
	}
	AnimationDirection GetDirection() const
	{
		return data.direction;
	}
	Sprite* GetSprite() const
	{
		return sprite;
	}

public:
	Animation(const string& _name, AnimationComponent* _owner, Sprite* _sprite,
		const AnimationData& _data);
	~Animation();

private:
	virtual void Register() override;
	void SetNext();
	Vector2i GetNewStart();

public:
	void Start();
	void Reset();
	void Stop();
	void Update();
};

