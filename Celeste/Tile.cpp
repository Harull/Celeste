#include "Tile.h"
#include "TextureManager.h"

Tile::Tile()
{
	shape = nullptr;
	type = ENTITY_NONE;
	position = Vector2f();
	size = Vector2f();
	path = string();
}

Tile::Tile(const Vector2f& _position, const Vector2f& _size, const string& _path, const EntityType& _type)
{
	type = _type;
	position = _position;
	size = _size;
	path = _path;

	shape = new RectangleShape(size);
	shape->setPosition(position);
	//shape->setOutlineThickness(-1.0f);
	shape->setOutlineColor(Color::Black);
	TextureManager::GetInstance().Load(shape, path);
}
