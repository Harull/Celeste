#include "TileEnd.h"
#include"EntityManager.h"
#include "LevelSelectorMenu.h"
#include "MenuOption.h"
#include "TimerManager.h"
#include "MenuEndLevel.h"
#include "SoundManager.h"

TileEnd::TileEnd(const EntityType _type, const Vector2f& _position, const Vector2f& _size, const string& _path, Grid* _owner)
	:Tile(_type, _position, _size, _path, _owner)
{
	collisionReaction = [this](int _collisionSide, int _collisionSideBinary) {GetHit(_collisionSide, _collisionSideBinary); };
	shape->setFillColor(Color::Transparent);
	isTangible = false;
}

void TileEnd::GetHit(int _collisionSide, int _collisionSideBinary)
{
	if (_collisionSideBinary != ENTITY_CHARACTER)return;

	Game::GetInstance().GetPlayer()->GetCharacter()->SetHasWon(true);
}

