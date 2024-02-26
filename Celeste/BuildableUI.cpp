#include "BuildableUI.h"
#include "Macro.h"
#include "UiManager.h"

//BuildableUI::BuildableUI(const string& _id, const Vector2f& _size, const Vector2f& _position, const string& _path, bool _start, bool _isLoop, bool _isInteractiveUi, const bool _isRepared)
//	:UiData(to_string(BACKGROUND) + _id + GetUniqueId(), _size, _position, _path, function<void()>(), {ST_VILLAGE}, _start, _isLoop, _isInteractiveUi, VS_UNSCOPED)
//{
//	windowSize = Game::GetWindowsSize();
//	isRepared = _isRepared;
//}
//
//BuildableUI::BuildableUI(const string& _id, const Vector2f& _size, const Vector2f& _position, const string& _path, const function<void()>& _function, bool _start, bool _isLoop, bool _isInteractiveUi, const bool _isRepared)
//	: UiData(to_string(BACKGROUND) + _id + GetUniqueId(), _size, _position, _path, _function, { ST_VILLAGE }, _start, _isLoop, _isInteractiveUi, VS_UNSCOPED)
//{
//	windowSize = Game::GetWindowsSize();
//	isRepared = _isRepared;
//}
//
//BuildableUI::BuildableUI(const string& _id, const float _size, const Vector2f& _position, const string& _path, const function<void()>& _function, bool _start, bool _isLoop, bool _isInteractiveUi, const bool _isRepared)
//	: UiData(to_string(BACKGROUND) + _id + GetUniqueId(), _size, _position, _path, _function, { ST_VILLAGE }, _start, _isLoop, _isInteractiveUi, VS_UNSCOPED)
//{
//	windowSize = Game::GetWindowsSize();
//	isRepared = _isRepared;
//}
//
//void BuildableUI::Upgrade()
//{
//}
