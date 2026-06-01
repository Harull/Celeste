#pragma once
#include "Player.h"
#include "UiManager.h"
#include "TimerManager.h"
#include "Macro.h"

class BuildableUI : public UiData
{
protected:
	Vector2f windowSize;
	bool isRepared;
public:
	BuildableUI(const string& _id, const Vector2f& _size, const Vector2f& _position, const string& _path,
		bool _start , bool _isLoop , bool _isInteractiveUi, const bool _isRepared);
	BuildableUI(const string& _id, const Vector2f& _size, const Vector2f& _position, const string& _path,
		const function<void()>& _function,bool _start, bool _isLoop, bool _isInteractiveUi, const bool _isRepared);
	BuildableUI(const string& _id, const float _size, const Vector2f& _position, const string& _path,
		const function<void()>& _function, bool _start, bool _isLoop, bool _isInteractiveUi, const bool _isRepared);

public:
	virtual void Upgrade();
};

