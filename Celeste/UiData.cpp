#include "UiData.h"
#include "TextureManager.h"
#include "UiManager.h"
#include "Macro.h"

UiData::UiData(const string& _id, const Vector2f& _size, const Vector2f& _position, const string& _path, function<void()> _callback,
	const std::vector<GameState>& _whenDisplayed, bool _start, bool _isLoop, bool _isInteractiveUi, const ViewState& _state)
	: IManageable(_id), Object(_size, _position, _path, _whenDisplayed)
{
	isInteractiveUi = _isInteractiveUi;
	isLoop = _isLoop;
	start = _start;
	callback = _callback;
	hasAlreadyBeenExecuted = false;
	isActive = true;
	state = _state;
	Register();
}

UiData::UiData(const string& _id, const float _radius, const Vector2f& _position, const string& _path, function<void()> _callback,
	const std::vector<GameState>& _whenDisplayed, bool _start, bool _isLoop, bool _isInteractiveUi, const ViewState& _state)
	: IManageable(_id), Object(_radius, _position, _path, _whenDisplayed)
{
	isInteractiveUi = _isInteractiveUi;
	isLoop = _isLoop;
	start = _start;
	callback = _callback;
	hasAlreadyBeenExecuted = false;
	isActive = true;
	state = _state;
	Register();
}

void UiData::Register()
{
	UiManager::GetInstance().Add(id, this);
}

void UiData::Execute()
{
	if (callback)
	{
		callback();
	}
}

void UiData::Start()
{
	start = true;
}

void UiData::Update()
{

}
