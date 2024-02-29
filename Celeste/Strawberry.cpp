#include "Strawberry.h"
#include"Game.h"
#include"Player.h"
Strawberry::Strawberry(const Vector2f& _position, const Vector2f& _size, const string& _path)
	:Tile(ENTITY_STRAWBERRY, _position, _size, _path)
{
	components.push_back(new AnimationComponent(
		this, _path,
		{ AnimationData("Idle", Vector2f(0.0f,0.0f), Vector2f(30.0f, 39.0f), READ_RIGHT, ANIM_DIR_NONE, true, 5, 0.5f) },
		ANIM_DIR_NONE
	));
	collisionReaction = [this](int _collisionSide, int _collisionSideBinary) {GetHit(_collisionSideBinary); };
}

void Strawberry::GetHit(int _collisionSideBinary)
{
	if (_collisionSideBinary != ENTITY_CHARACTER)return;
	tangible = false;
	shape->setFillColor(Color::Transparent);
	GetComponent<AnimationComponent>()->Finish();
	Game::GetInstance().GetPlayer()->GetPlayerData().IncreaseStrawBerry();

}
