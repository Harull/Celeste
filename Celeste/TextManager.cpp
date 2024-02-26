#include "TextManager.h"

void TextManager::DisplayAllTexts()
{
	sf::RenderWindow& _mainWindow = Game::GetWindow();
	const GameState& _gameState = Game::GetGameState();
	const auto& _allValues = GetAllValues();

	for (TextData* _text : _allValues)
	{
		const std::vector<GameState>& _whendisplayed = _text->GetWhenDisplayed();
		for (const GameState& _currentState : _whendisplayed)
		{
			if (_currentState == _gameState)
			{
				_mainWindow.draw(*_text);
				break;
			}
		}
	}
}

void TextManager::CloseAll()
{
	for (TextData* _textData : GetAllValues())
	{
		if (Contains(_textData->GetID(), "Uncloseable"))
		{
			continue;
		}
		//_textData->SetToBeRemove(true);
	}
}


bool TextManager::Contains(const string& _id, const string& _value)
{
	if (_id.find(_value) != string::npos)
	{
		return true;
	}
	return false;
}

