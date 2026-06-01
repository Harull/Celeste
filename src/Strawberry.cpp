#include "../include/Strawberry.h"
#include "../include/Game.h"
#include "../include/Player.h"
#include "../include/SoundManager.h"
#include "../include/Macro.h"

Strawberry::Strawberry(const Vector2f& _position, const Vector2f& _size, Grid* _owner, const string& _path)
	:Tile(ENTITY_STRAWBERRY, _position, _size, _path, _owner)
{
	components.push_back(new AnimationComponent(
		this, _path,
		{ AnimationData(S_APPEND("IdleStrawberry"), Vector2f(0.0f,0.0f), Vector2f(120.42f, 150.0f), READ_RIGHT, ANIM_DIR_NONE, true, 7, 0.1f) },
		ANIM_DIR_NONE
	));
	collisionReaction = [this](int _collisionSide, int _collisionSideBinary) {GetHit(_collisionSideBinary); };
	isUsed = false;
	isTangible = false;
}

void Strawberry::GetHit(int _collisionSideBinary)
{
	if (_collisionSideBinary != ENTITY_CHARACTER)return;
	if (isUsed)return;
	SoundManager::GetInstance().Play("strawberry_red_get_1000.wav");
	isUsed = true;
	shape->setFillColor(Color::Transparent);
	GetComponent<AnimationComponent>()->Finish();
	Game::GetInstance().GetPlayer()->GetPlayerData().IncreaseStrawBerry();

}
