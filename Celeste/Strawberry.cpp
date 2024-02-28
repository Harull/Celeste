#include "Strawberry.h"

Strawberry::Strawberry(const Vector2f& _position, const Vector2f& _size, const string& _path)
	:Tile(ENTITY_STRAWBERRY, _position, _size, _path)
{
	components.push_back(new AnimationComponent(
		this, _path,
		{ AnimationData("Idle", Vector2f(0.0f,0.0f), Vector2f(12.0f, 13.0f), READ_RIGHT, ANIM_DIR_NONE, true, 3, 0.5f) },
		ANIM_DIR_NONE
	));
}
