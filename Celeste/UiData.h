#pragma once
#include "IManageable.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <functional>
#include "Object.h"

using namespace std;
using namespace sf;

enum ViewState;

class UiData : public IManageable<string>, public Object
{
	bool isInteractiveUi;
	bool isLoop;
	bool start;
	bool hasAlreadyBeenExecuted;
	bool isActive;
	function<void()> callback;

public:
	bool IsInteractiveUi() const
	{
		return isInteractiveUi;
	}

	bool IsStarting() const
	{
		return start;
	}

	bool IsLoop() const
	{
		return isLoop;
	}

	bool IsExecuted() const
	{
		return hasAlreadyBeenExecuted;
	}

	bool IsActive() const
	{
		return isActive;
	}

	void SetExecuted(const bool _hasAlreadyBeenExecuted)
	{
		hasAlreadyBeenExecuted = _hasAlreadyBeenExecuted;
	}

	void SetIsActive(const bool _isActive)
	{
		isActive = _isActive;
	}

public:
	UiData(const string& _id, const Vector2f& _size, const Vector2f& _position, const string& _path, function<void()> _callback,
		const std::vector<GameState>& _whenDisplayed, bool _start = true, bool _isLoop = false, bool _isInteractiveUi = false, const ViewState& _state = VS_DEFAULT);
	UiData(const string& _id, const float _radius, const Vector2f& _position, const string& _path, function<void()> _callback,
		const std::vector<GameState>& _whenDisplayed, bool _start = true, bool _isLoop = false, bool _isInteractiveUi = false, const ViewState& _state = VS_DEFAULT);

public:

	virtual void Update();
	void Start();
	virtual void Execute();
	// Hérité via IManagable
	void Register() override;


};

