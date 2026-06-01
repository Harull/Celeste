#include "../include/UiData.h"
#include "../include/TextureManager.h"
#include "../include/UiManager.h"
#include "../include/Macro.h"

UiData::UiData(const string& _id, const Vector2f& _size, const Vector2f& _position, const string& _path, function<void()> _callback,
	 bool _start, bool _isLoop, bool _isInteractiveUi)
	: IManageable(_id)
{
	isInteractiveUi = _isInteractiveUi;
	isLoop = _isLoop;
	start = _start;
	callback = _callback;
	hasAlreadyBeenExecuted = false;
	isActive = true;
	Register();
}

UiData::UiData(const string& _id, const float _radius, const Vector2f& _position, const string& _path, function<void()> _callback,
	 bool _start, bool _isLoop, bool _isInteractiveUi)
	: IManageable(_id)
{
	isInteractiveUi = _isInteractiveUi;
	isLoop = _isLoop;
	start = _start;
	callback = _callback;
	hasAlreadyBeenExecuted = false;
	isActive = true;
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
