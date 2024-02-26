#include "TextData.h"
#include "TextManager.h"
#include "FontManager.h"
#include <string>
#include "Macro.h"


TextData::TextData(const string& _id, const std::string& _text, const sf::Vector2f& _position, const unsigned int _characterSize, const vector<GameState>& _whenDisplayed,
	const std::string& _fontPath) : IManageable(_id)
{
	whenDisplayed = _whenDisplayed;
	setString(_text);
	setPosition(_position);
	setCharacterSize(_characterSize);
	setFillColor(Color::Red);
	FontManager::GetInstance().Load(this, _fontPath);
	setOrigin(getGlobalBounds().getSize() / 2.f);
	Register();
}

void TextData::Register()
{
	TextManager::GetInstance().Add(id, this);
}