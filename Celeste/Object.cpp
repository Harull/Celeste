#include "Object.h"
#include "TextureManager.h"
#include "FontManager.h"

Object::Object(const Vector2f& _size, const Vector2f& _position, const string& _path, const std::vector<GameState>& _whenDisplayed)
{
	text = nullptr;
	whenDisplayed = _whenDisplayed;
	shape = new RectangleShape(_size);
	shape->setOrigin(_size / 2.f);
	shape->setPosition(_position);

	TextureManager::GetInstance().Load(shape, _path);
}

Object::Object(const float _size, const Vector2f& _position, const string& _path, const std::vector<GameState>& _whenDisplayed)
{
	text = nullptr;
	whenDisplayed = _whenDisplayed;
	shape = new CircleShape(_size);
	shape->setOrigin(_size / 2.f, _size / 2.f);
	shape->setPosition(_position);

	TextureManager::GetInstance().Load(shape, _path);
}

Object::Object(const int _textSize, const Vector2f& _position, const string& _path, const string& _text, const std::vector<GameState>& _whenDisplayed)
{
	shape = nullptr;
	whenDisplayed = _whenDisplayed;
	text = new Text();
	text->setCharacterSize(_textSize);
	text->setPosition(_position);
	text->setString(_text);

	FontManager::GetInstance().Load(text, _path);
}
