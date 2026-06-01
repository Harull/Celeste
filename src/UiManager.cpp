#include "../include/UiManager.h"
#include "../include/Game.h"
#include "../include/BuildableUI.h"


//void UiManager::Update()
//{
//	sf::RenderWindow& _mainWindow = Game::GetWindow();
//	sf::Vector2i _mousePos = Mouse::getPosition(_mainWindow);
//	Vector2f _worldPos = _mainWindow.mapPixelToCoords(_mousePos);
//
//	auto _allInteractiveUi = UiManager::GetInstance().GetAllInteractiveUi();
//	for (auto _iterator = _allInteractiveUi.rbegin(); _iterator != _allInteractiveUi.rend(); _iterator++)
//	{
//		Game::SetViewState((*_iterator)->GetState());
//		_mousePos = Mouse::getPosition(_mainWindow);
//		_worldPos = _mainWindow.mapPixelToCoords(_mousePos);
//		
//		BuildableUI* _buildableUI = dynamic_cast<BuildableUI*>(*_iterator);
//
//		UiData* _uiData = *_iterator;
//		Shape* _shape = _uiData->GetShape();
//		FloatRect _rect = _shape->getGlobalBounds();
//
//		_uiData->Update();
//
//		if (_uiData->IsStarting() && _uiData->IsLoop())
//		{
//			_uiData->Execute();
//		}
//
//		if (_uiData->IsStarting())
//		{
//			if (!_uiData->IsExecuted())
//			{
//				_uiData->Execute();
//				_uiData->SetExecuted(true);
//			}
//		}
//
//		if (_uiData->IsInteractiveUi())
//		{
//			if (_rect.contains(Vector2f(_worldPos)))
//			{
//				_shape->setOutlineThickness(2.f);
//				_shape->setOutlineColor(Color::Blue);
//				return;
//			}
//			else
//			{
//				Reset();
//			}
//		}
//	}
//}
//
//void UiManager::CloseAll()
//{
//	for (UiData* _uiData : GetAllValues())
//	{
//		if (Contain(_uiData->GetID(),"Uncloseable"))
//		{
//			continue;
//		}
//		_uiData->SetToBeRemove(true);
//	}
//}
//
//void UiManager::CloseWithId(const vector<string>& _ids)
//{
//	for (UiData* _uiData : GetAllValues())
//	{
//		for (string _id : _ids)
//		{
//			if (_uiData->GetID() == _id)
//			{
//				_uiData->SetToBeRemove(true);
//			}
//		}
//	}
//}
//
//void UiManager::DisplayAllUi() const
//{
//	sf::RenderWindow& _mainWindow = Game::GetWindow();
//	View* _view = Game::GetCurrentView();
//	const GameState& _gameState = Game::GetGameState();
//	const auto& _allUi = GetAllValues();
//
//	for (UiData* _ui : _allUi)
//	{
//		const std::vector<GameState>& _whendisplayed = _ui->GetWhenDisplayed();
//		Game::SetViewState(_ui->GetState());
//		for (const GameState& _currentState : _whendisplayed)
//		{
//			BuildableUI* _buildableUI = dynamic_cast<BuildableUI*>(_ui);
//			if (!_buildableUI)
//			{
//				if (_currentState == _gameState)
//				{
//					_ui->SetIsActive(true);
//					_mainWindow.draw(*_ui->GetShape());
//					break;
//				}
//				else
//				{
//					_ui->SetIsActive(false);
//				}
//			}
//			else
//			{
//				if (_currentState == _gameState)
//				{
//					_buildableUI->SetIsActive(true);
//					_mainWindow.draw(*_buildableUI->GetShape());
//					break;
//				}
//				else
//				{
//					_buildableUI->SetIsActive(false);
//				}
//			}
//
//		}
//	}
//	
//}
//
//bool UiManager::Contain(const string& _id, const string& _value)
//{
//	if (_id.find(_value) != string::npos)
//	{
//		return true;
//	}
//	return false;
//}
//
//void UiManager::Reset()
//{
//	for (UiData* _uiData : GetAllValues())
//	{
//		Shape* _shape = _uiData->GetShape();
//		_shape->setOutlineThickness(0.f);
//	}
//}
