#include "../include/TileEnd.h"
#include "../include/EntityManager.h"
#include "../include/LevelSelectorMenu.h"
#include "../include/MenuOption.h"
#include "../include/TimerManager.h"
#include "../include/MenuEndLevel.h"
#include "../include/SoundManager.h"

TileEnd::TileEnd(const EntityType _type, const Vector2f& _position, const Vector2f& _size, const string& _path, Grid* _owner)
	:Tile(_type, _position, _size, _path, _owner)
{
	collisionReaction = [this](int _collisionSide, int _collisionSideBinary) {GetHit(_collisionSide, _collisionSideBinary); };
	shape->setFillColor(Color::Transparent);
	isTangible = false;
	components.push_back(new AnimationComponent(
		this, "../../../../assets/Cassette.png",
		{ AnimationData("IddleCassette", Vector2f(0.0f,0.0f), Vector2f(72.f, 52.0f), READ_RIGHT, ANIM_DIR_NONE, true, 32, 0.1f)},
		ANIM_DIR_NONE
	));
}

void TileEnd::GetHit(int _collisionSide, int _collisionSideBinary)
{
	if (_collisionSideBinary != ENTITY_CHARACTER)return;

	Game::GetInstance().GetPlayer()->GetCharacter()->SetHasWon(true);
}

